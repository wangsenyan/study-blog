//OpenSSL,HMAC,加密,解密,签名,验证功能
const crypto = require('crypto');
    const secret = "abcdefg";
    const hash = crypto.createHmac('sha256',secret)
                 .update('I love cupcakes')
                 .digest('hex');
    console.log(hash);

    const cert1 = new crypto.Certificate();
    const cert2 = crypto.Certificate();

