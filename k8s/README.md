### [kubernetes](https://kubernetes.io/zh/docs/reference/)


### 单节点部署

```sh
#描述
kubectl describe pod [pod-name]
#取消单节点限制
kubectl taint nodes --all node-role.kubernetes.io/master-

#运行 dry-run 试运行  -o yaml输出yaml
kubectl create deployment tomcat6 --image=tomcat:6.0.53-jre8 [--dry-run] -o yaml
#以yaml格式输出pod-name的配置
kubectl get pod <pod-name> -o yaml 
#先create后才能暴露
#Pod的80映射容器的8080;service 会代理Pod的80,NodePort随机端口
kubectl expose deployment tomcat6 --port=80 --target-port=8080 --type=NodePort

#查看service|pods|nodes
kubectl get [svc|pods|nodes] -o wide

#扩容tomcat6
kubectl scale --replicas=2 deployment tomcat6 
#缩容
kubectl scale --replicas=1 deployment tomcat6 
#删除资源,service,pod
kubectl delete [deployment|service]

kubectl apply -f  config.yaml

#强制删除namespace
kubectl delete namespace [namespace]
kubectl get pods --namespace=[namespace]
```

### yml模板

### Controller
* ReplicaSet 副本集
* Deployments == Pods + ReplicaSets
* StatefulSet 有状态应用
* DeamonSet 确保全部或某些节点运行一个Pod的副本

### Service
* 统一pod
* label ---> Label selector