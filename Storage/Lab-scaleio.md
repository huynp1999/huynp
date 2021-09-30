- scaleio 2.5
- centos 7
- 3 node cluster

## 1. Cài đặt java jdk 1.8
Kiểm tra xem các bản java đã cài đặt trước đó và gỡ cài đặt, ví dụ `java-1.7.0-openjdk`:

    yum update
    rpm -qa | grep -E '^open[jre|jdk]|j[re|dk]'
    yum remove java-1.7.0-openjdk

Tải về jdk package tại [đây](https://www.oracle.com/java/technologies/javase/javase8-archive-downloads.html) và cài đặt:

    rpm -ivh jdk-8u25-linux-x64.rpm
    
Ssetup các biến môi trường

    cat << EOF > /etc/profile.d/java.sh
    #!/bin/bash
    JAVA_HOME=/usr/java/jdk1.8.0_25/
    PATH=$JAVA_HOME/bin:$PATH
    export PATH JAVA_HOME
    export CLASSPATH=.
    EOF

    chmod +x /etc/profile.d/java.sh
    source /etc/profile.d/java.sh
    alternatives --install /usr/bin/java java /usr/java/jdk1.8.0_25/jre/bin/java 20000
    alternatives --install /usr/bin/jar jar /usr/java/jdk1.8.0_25/bin/jar 20000
    alternatives --install /usr/bin/javac javac /usr/java/jdk1.8.0_25/bin/javac 20000
    alternatives --install /usr/bin/javaws javaws /usr/java/jdk1.8.0_25/jre/bin/javaws 20000
    alternatives --set java /usr/java/jdk1.8.0_25/jre/bin/java
    alternatives --set jar /usr/java/jdk1.8.0_25/bin/jar
    alternatives --set javac /usr/java/jdk1.8.0_25/bin/javac
    alternatives --set javaws /usr/java/jdk1.8.0_25/jre/bin/javaws
    
Kiểm tra:
    
    java -version
    
## 2. Deploy Scaleio
Scaleio sẽ được deploy qua một installer gateway. Cài đặt packet gateway dành cho Centos:

    GATEWAY_ADMIN_PASSWORD=<new_GW_admin_password> rpm -U EMC-ScaleIO-gateway-2.5-0.254.x86_64.rpm --nodeps
    
Nếu gặp lỗi `Cannot query status of the EMC ScaleIO Gateway.` thì cần xem lại các cài đặt java, cần đúng 1.8.

    
