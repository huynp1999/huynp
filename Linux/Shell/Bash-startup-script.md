# Bash script
Nhằm thay thế cho những tập lệnh lặp lại, chỉ cần viết một lần và chạy lại bất kỳ khi nào.
Một file script trên môi trường linux có đuôi .sh và .bat trên môi trường windows.

## Tạo bash script
1. Tạo một file script.sh:

```#!/bin/bash
echo “Hello World !”
```

Trong đó, dòng đầu tiên để khai báo loại ngôn ngữ sử dụng là bash, sau dấu #! là đường dẫn trỏ đến lệnh bash.

2. Thực thi script:

`bash script.sh`

3. Cách thực thi 2:
Cấp quyền execute cho nó bằng lệnh
`chmod +x  script.sh`
Sau đó chạy bằng lệnh sẽ cho ra kết quả tương tự
`./script.sh `

## Input
Gồm 4 kiểu biến dữ liệu:
- Interger
- String
- Array
- Constant

1. Khai báo sẵn
Ví dụ với kiểu int và str:
```
name=”huy”
age=22
echo $name
echo $age
```

Khi chạy `./script.sh` sẽ cho ra kết quả dữ liệu của biến name và age.

2. Truyền tham số
```
name=$1
age=$2
echo “Name : ” $name
echo “Age : ” $age
```

Truyền tham số vào name và age:

`./script.sh huy 22` 

3. Ví dụ

Thực hiện phép tính `a*(b+c)`
```
#!/bin/bash
kq=$(($1*$(($2+$3))))
echo "=$kq"
```

Với input `./script.sh 2 3 2` sẽ có output `=10`
## Lệnh điều kiện
```
#!/bin/bash
if [ $1 -eq 0 ]
then
echo "Bang khong"
else
kq=$(($1*$(($2+$3))))
echo "=$kq"
fi
```
sẽ cho ra kết quả
```
./script.sh 2 3 0
Bang khong
```
với `-eq` = **eq**ual, `-ge` = **g**reater than or **e**qual,...

# Startup script
Có nhiều cách  chạy một script mỗi khi khởi động hoặc reboot máy, ví dụ như `crontab -e` nhưng ví dụ ở đây sẽ làm việc với `systemd` vì cho độ tin cậy cao nhất.

Với một bash script sau, dùng để in ra màn hình chuỗi ký tự mỗi khi một người dùng đăng nhập với `/etc/motd` (message of the day):

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/startup3.png)

Tạo một file .service tại `/etc/systemd/system` với nội dung cơ bản gồm
- thông tin
- đường dẫn file script
- áp dụng cho đa người dùng 

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/startup2.png)

File .service này cần được cấp quyền `chmod -x` để có thể thực hiện `systemctl enable`.

Kết quả:
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/startup1.png)

