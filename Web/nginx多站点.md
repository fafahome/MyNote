# nginx 多站点配置
*在 centos7 下测试通过*
下面是具体的配置过程：
1、在 /etc/nginx 下创建 vhosts 目录
```
mkdir /etc/nginx/vhosts
```
2、在 /etc/nginx/vhosts/ 里创建一个名字为 fafa.tv.conf 的文件，把以下内容拷进去
```
server {
        listen  80;
        server_name  fafa.tv www.fafa.tv;
        access_log  /www/access_fafatv.log  main;
        location / {
            root   /www/fafa.tv;
            index  index.php index.html index.htm;
        }
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   /usr/share/nginx/html;
        }
       # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
        location ~ .php$ {
            fastcgi_pass   127.0.0.1:9000;
            fastcgi_index  index.php;
            fastcgi_param  SCRIPT_FILENAME  /www/fafa.tv/$fastcgi_script_name;
            include        fastcgi_params;
        }
        location ~ /.ht {
            deny  all;
        }
}
```
3、在 /etc/nginx/vhosts/ 里创建一个名字为 fafa.la.conf 的文件，把以下内容拷进去
```
server {
        listen  80;
        server_name  fafa.la www.fafa.la;
        access_log  /www/access_fafala.log  main;
        location / {
            root   /www/fafa.la;
            index  index.php index.html index.htm;
        }
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   /usr/share/nginx/html;
        }
       # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
        location ~ .php$ {
            fastcgi_pass   127.0.0.1:9000;
            fastcgi_index  index.php;
            fastcgi_param  SCRIPT_FILENAME  /www/fafa.la/$fastcgi_script_name;
            include        fastcgi_params;
        }
        location ~ /.ht {
            deny  all;
        }
}
```
4、打开 /etc/nginix.conf 文件，在相应位置加入 include 把以上2个文件包含进来
```
user  nginx;
worker_processes  1;
# main server error log
error_log       /var/log/nginx/error.log ;
pid     /var/run/nginx.pid;
events {
        worker_connections  1024;
}
# main server config
http {
        include       mime.types;
        default_type  application/octet-stream;
        log_format  main  '$remote_addr - $remote_user [$time_local] $request '
                      '"$status" $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';
        sendfile        on;
        #tcp_nopush     on;
        #keepalive_timeout  0;
        keepalive_timeout  65;
        gzip  on;
        server {
                listen         80;
                server_name     _;
                access_log      /var/log/nginx/access.log main;
                server_name_in_redirect  off;
                location / {
                        root  /usr/share/nginx/html;
                        index index.html;
                }
        }
    # 包含所有的虚拟主机的配置文件
    include /etc/nginx/vhosts/*;
}
```