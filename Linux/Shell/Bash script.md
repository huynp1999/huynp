# Bash script
Nhằm thay thế cho những tập lệnh lặp lại, chỉ cần viết một lần và chạy lại bất kỳ khi nào.
Một file script trên môi trường linux có đuôi .sh và .bat trên môi trường windows.

## Tạo bash script
1. Tạo một file script.sh:

```#!/bin/bash
echo “Hello World !”
```

Trong đó, dòng đầu tiên để khai báo loại ngôn ngữ sử dụng là bash, sau dấu #! là đường dẫn trỏ đến lệnh bash.

1.1. Thực thi script:

`$bash script.sh`

1.2. Cách thực thi 2:
Cấp quyền execute cho nó bằng lệnh
`$chmod +x  script.sh`
Sau đó chạy bằng lệnh sẽ cho ra kết quả tương tự

`$./script.sh `

## Input
Gồm 4 kiểu biến dữ liệu:
- Interger
- String
- Array
- Constant

1.1 Khai báo sẵn
Ví dụ với kiểu int và str:
```
name=”huy”
age=22
echo $name
echo $age
```

Khi chạy `./script.sh` sẽ cho ra kết quả dữ liệu của biến name và age.

1.2 Truyền tham số
```
name=$1
age=$2
echo “Name : ” $name
echo “Age : ” $age
```

Truyền tham số vào name và age:

`./script.sh huy 22` 

1.3 Ví dụ

Thực hiện phép tính `a*(b+c)`
```
kq=$($1 * ($2 + $3))
echo “$($1 * ($2 + $3)) = $kq”
```

Với input `./script.sh 2 1 3` sẽ có output `2 * (1 + 3) = 8`
