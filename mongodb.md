1. rm -rf 文件夹

 ```sh
  rm -f 文件  
  rar x .rar  //解压rar文件  
  tar zxvf 原文件夹 -C 指定文件夹 //解压缩tar  
  mv old new  //更改文件件名  
  mkdir 文件名 //新建文件夹  
 ```
2. apt-get

  ```sh
  sudo apt-get update //更新数据库缓存  
  apt-get sourse 
  ```  
3. sudo service mongod stop
  ```sh
  sudo service mongod restart  
  mongo --host 127.0.0.1:27017  
  
  sudo apt-get purge mongodb-org*  
  sudo rm -r /var/log/mongodb  
  sudo rm -r /var/lib/mongodb  
  ```
4. npm install jade --save
 ```sh
  npm install express --save 
 ```  
  express和jade安装到一个文件夹

5. ps -ef |grep mongo

 ```sh
  kill 进程  
  netstat -anp|more  
  kill -9 进程  
  mongod --fork --dbpath=/root/mongodb/data/db 后台运行  
  ./mongod    use admin  db.shutdownServer()  
  ```

6. 将win平台上的nodejs代码移植到Ubuntu14.04上时，出现strict模式，大部分原因是       mongod的原因。上传的时候删除原来的node_moudles和.git等无关的文件。打包上传。然    后分别安装 npm install xxx --save(test，mocha时候用)。express重新安装一遍。  不用管connect-mongo版本。启动时杀死mongod进程（或者重新安装）
