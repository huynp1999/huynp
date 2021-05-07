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
kq=$(($3*$(($1+$2))))
echo "=$kq"
```

Với input `./script.sh 2 3 2` sẽ có output `=10`
## Lệnh điều kiện
```
#!/bin/bash
if [ $3 -eq 0 ]
then
echo "Bang khong"
else
kq=$(($3*$(($1+$2))))
echo "=$kq"
fi
```
sẽ cho ra kết quả
```
./script.sh 2 3 0
Bang khong
```
với `-eq` = **eq**ual, `-ge` = **g**reater than or **e**qual,...
