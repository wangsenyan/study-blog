var mysql = require('../../utils/mysql.js');
var async = require('async');
var rest = require('restler');
var utils = require('utility');
var request = require('superagent');
var apikey = "f607aace16ec412e8913cabf133f0af4";
var secret_key = "8CC90277703A4A59";
var host = "api.testin.cn";
exports.map = function (app) {

  /**
   * 上传认证材料
   * result 0=失败，1=成功
   */
  app.get("/testin/enterprise/auth", function (req, res) {
    var opt = {
      eFullName: req.body.eFullName,
      license: req.body.license,
    }
    var sid = null;
    async.waterfall([
      function (cb) {
        login(req, function (e, r) {
          if (e) {
            return cb(e)
          }
          if (r.code != 0) {
            return cb(r)
          }
          sid = r.data.result;
          cb(null);
        })
      },
      function (cb) {
        enterpriseAuth(opt.eFullName, opt.license, sid, function (e, r) {
          if (e) {
            return cb(e)
          }
          if (r.code != 0) {
            return cb(r);
          }
          cb(e, r)
        })
      }
    ])
  })
  /**
   * 获取企业认证信息
   * authStatus 1=认证通过，2=待审核，3=审核失败，4=未认证
   */
  app.get("/testin/enterprise/quotaInfo", function (req, res) {
    var sid = null;
    async.waterfall([
      function (cb) {
        login(req, function (e, r) {
          if (e) {
            return cb(e)
          }
          if (r.code != 0) {
            return cb(r);
          }
          sid = r.data.result;
          cb(null);
        })
      },
      function (cb) {
        enterpriseQuotaInfo(sid, function (e, r) {
          if (e) {
            return cb(e)
          }
          if (r.code != 0) {
            return cb(r);
          }
          cb(e, r)
        })
      }
    ], function (err, result) {
      if (err) {
        return res.ok({ authStatus: 4 })
      }
      return res.ok({ authStatus: result.authStatus });
    })
  })

  /**
   * 提测
   * enterprise 企业1 非企业0
   * packageUrl apk 下载地址
   * upkId 包id
   */
  app.post("/testin/realtest", function (req, res) {

    var opt = {
      userId: req.session.userid,
      enterprise: req.body.enterprise,
      packageUrl: req.body.packageUrl,
      upkId: req.body.upkId,
      testDescr: req.body.testDescr
    }
    var sid = null;
    async.waterfall([
      function (cb) {
        var sql = "SELECT testInTimes,testInCT FROM TB_Enterprise_User WHERE enterUserId = :userId";
        mysql.wpool.query(sql, opt, function (e, r) {
          if (e) {
            return cb(e);
          }
          opt.times = r[0].testInTimes;
          var testInCT = r[0].testInCT;
          var minTime = (new Date(utils.YYYYMMDD())).getTime();
          if (testInCT > minTime) {
            if ((opt.enterprise == 1 && times == 3) || ((opt.enterprise == 0 && times == 1))) {
              return res.err(372, "当天的次数已满！");
            }
            opt.times++;

          } else {
            opt.times = 1;
          }
          if (!testInCT) {
            opt.times = 1;
          }
          cb(null);
        })
      },
      function (cb) {
        if (opt.enterprise == 1) {
          return cb(null);
        }
        register(req, function (e, r) {
          if (e) {
            return cb(e);
          }
          if (r.code != 0) {
            return cb(r);
          }
          cb(null);
        })
      },
      function (cb) {
        login(req, function (e, r) {
          if (e) {
            return cb(e)
          }
          if (r.code != 0) {
            return cb(r);
          }
          sid = r.data.result;
          cb(null);
        })
      },
      function (cb) {
        var quotaCode = "401201";
        if (opt.enterprise == 1) {
          quotaCode = "401202";
        }
        taskAdd(sid, quotaCode, packageUrl, opt.testDescr, function (e, r) {
          if (e) {
            return cb(e);
          }
          if (r.code != 0) {
            return cb(r);
          }
          opt.adaptId = r.data.result;
          cb(null);
        })
      },
      function (cb) {
        opt.ct = (new Date()).getTime();
        var sql = "UPDATE cad_unpack SET testInState = 1,testInCT =:ct,adaptId=:adaptId WHERE upkId = :upkId;UPDATE TB_Enterprise_User SET testInCT = :ct ,testInTimes = :times WHERE enterUserId = :userId";
        mysql.wpool.query(sql, opt, function (e, r) {
          cb(e, r)
        })
      }
    ], function (err, result) {
      if (err) {
        return res.err(371, '提交测试失败！');
      }
      res.ok();
    })
  })

  function login (req, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "user",
      op: "AppUser.login",
      timestamp: (new Date()).getTime(),
      data: { thirdUniqueid: req.session.userid }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function logout (req, sid, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "user",
      op: "Login.logout",
      timestamp: (new Date()).getTime(),
      data: { sid: sid }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })

  }
  function register (req, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "user",
      op: "Enterprise.register",
      timestamp: (new Date()).getTime(),
      data: { "eFullName": "柚子（北京）移动技术有限公司", "email": req.session.email, "thirdUniqueid": req.session.userid },
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function enterpriseAuth (eFullName, license, sid, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "user",
      op: "Enterprise.auth",
      timestamp: (new Date()).getTime(),
      data: {
        eFullName: eFullName,
        license: license
      },
      sid: sid
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function enterpriseQuotaInfo (sid, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "user",
      op: "Enterprise.quotaInfo",
      timestamp: (new Date()).getTime(),
      sid: sid
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function taskAdd (sid, quotaCode, packageUrl, testDescr, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "app",
      op: "Task.add",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: {
        appinfo: { packageUrl: packageUrl, syspfId: 1 },
        callbackUrl: "https://pwd.apicloud.com/testin/callback",
        quotaCode: quotaCode,
        taskDescr: testDescr
      }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function taskOverview (sid, taskid, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "app",
      op: "Task.overview",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: { taskid: taskid }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function taskDetails (sid, taskid, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "app",
      op: "Task.details",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: { taskid: taskid }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function taskCancel (sid, taskid, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "app",
      op: "Task.cancel",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: {
        taskid: taskid
      }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  /**
   * data{ page, pageSize}
   * 
  */
  function taskList (sid, page, pageSize, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "portal",
      op: "Task.list",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: { page: page, pageSize: pageSize }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function reportUrl (sid, taskid, subtaskid, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "report",
      op: "Report.url",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: {
        taskid: taskid,
        subtaskid: subtaskid
      }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  /**
   * data {} 包括 taskid,page,pageSize
   */
  function reportList (sid, taskid, page, pageSize, cb) {
    var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "report",
      op: "Report.url",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: { taskid: taskid, page: page, pageSize: pageSize }
    }
    params.sig = sig(params);
    post(host, params, function (e, r) {
      cb(e, r);
    })
  }
  function uploadImage (sid, suffix, cb) {
    var params = {
      apikey: apikey,
      mkey: "file",
      action: "file",
      op: "FileApi.upload",
      timestamp: (new Date()).getTime(),
      sid: sid,
      data: {
        "suffix": suffix
      }
    }
    var url = "https://fileupload.testin.cn/uploadService"
    params.sig = sig(params)
    fs.readFile('image.png', function (err, d) {
      if (err) { return cb(err) }
      else {
        request.post(url)
          .set("Content-Type", "image/png")
          .set("uploadParam", JSON.stringify(params))
          .attach('image', data)
          .end(function (e, r) {
            cb(e, r)
          })
      }
    })
  }
  /**
   *签名，去掉json报文无用的空格和回车符
   *缺secret_key
   */
  function sig (params) {
    var keys = [];
    for (var i in params) {
      keys.push(i);
    }
    keys.sort();
    var sig = "";
    for (var i in keys) {
      if (typeof params[keys[i]] === 'object') {
        sig += keys[i] + "=" + JSON.stringify(params[keys[i]]);
      } else {
        sig += keys[i] + "=" + params[keys[i]];
      }
    }
    sig += secret_key;
    sig = sig.replace(/\r\n/g, "")
      .replace(/\n/, "")
      .replace(/\s/, "")
    return utils.md5(sig);
  }
  function post (url, params, cb) {
    rest.postJson(url, params).on('complete', function (data, response) {
      //console.log(err);
      if (response.statusCode == 200) {
        cb(null, JSON.parse(data));
      } else {
        cb(data, null);
      }
    });
  }
}
