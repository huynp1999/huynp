#!/bin/bash
echo "**********************************************************";
echo "Install packets";
echo "**********************************************************";
sudo apt install -y apache2 mysql-client mysql-server php libapache2-mod-php
sudo apt install -y graphviz aspell ghostscript clamav php7.2-pspell php7.2-curl php7.2-gd php7.2-intl php7.2-mysql php7.2-xml php7.2-xmlrpc php7.2-ldap php7.2-zip php7.2-soap php7.2-mbstring
sudo service apache2 restart
sudo apt install -y git
echo "**********************************************************";
echo "Clone Moodle and make branch";
echo "**********************************************************";
cd /opt
sudo git clone git://git.moodle.org/moodle.git
cd moodle
sudo git branch -a
sudo git branch --track MOODLE_38_STABLE origin/MOODLE_38_STABLE
sudo git checkout MOODLE_38_STABLE
echo "**********************************************************";
echo "Copy local repository to /var/www/html/ ";
echo "**********************************************************";
sudo cp -R /opt/moodle /var/www/html/
sudo mkdir /var/moodledata
sudo chown -R www-data /var/moodledata
sudo chmod -R 777 /var/moodledata
sudo chmod -R 0755 /var/www/html/moodle 
echo "**********************************************************";
echo "Setup MySQL Server";
echo "**********************************************************";
sudo sed -i '/^skip-external-locking/a default_storage_engine = innodb\ninnodb_file_per_table = 1\ninnodb_file_format = Barracuda' /etc/mysql/mysql.conf.d/mysqld.cnf
sudo service mysql restart
echo "**********************************************************";
echo "SQL query";
echo "**********************************************************";
sudo mysql -e "CREATE DATABASE moodle DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;"
sudo mysql -e "create user 'moodleuser'@'localhost' IDENTIFIED BY 'password';"
sudo mysql -e "GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,CREATE TEMPORARY TABLES,DROP,INDEX,ALTER ON moodle.* TO 'moodleuser'@'localhost';"
echo "**********************************************************";
echo "COMPLETE";
echo "**********************************************************";
sudo chmod -R 777 /var/www/html/moodle
sudo chmod -R 0755 /var/www/html/moodle
