1. `unexpected error storing fake SSL Cert: could not create PEM certificate file /etc/ingress-controller/ssl/default-fake-certificate.pem: open /etc/ingress-controller/ssl/default-fake-certificate.pem: permission denied`

[solution](https://github.com/kubernetes/ingress-nginx/issues/4061) 
Change runAsUser: 33 to runAsUser: 101.