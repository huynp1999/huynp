# Repository
Là nơi lưu trữ những thông tin project nhằm hiển thị, sửa đổi và chia sẻ cho những người khác.

Khởi tạo tại:
Picture: ![Alt](https://github.com/huynp1999/huynp/blob/master/New%20r.png)

Sau khi có URL, sử dụng `git clone` để clone repo về máy của mình:
```$ git clone hhttps://github.com/huynp1999/huynp
Cloning into 'hoc-git'...
warning: You appear to have cloned an empty repository.
Checking connectivity... done
```
Tạo file và add, commit:
```$ echo "# Thực hành Git cơ bản" > README.md
$ git add README.md 
$ git commit -m "sample commit"
[master 39eb20b] sample commit
 1 file changed, 1 insertion(+)
 create mode 100644 README.md
 ```
 Đẩy file được commit lên Github: (tại repo huynp)
 ```$ git push origin master
Counting objects: 5, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (4/4), done.
Writing objects: 100% (5/5), 577 bytes | 0 bytes/s, done.
Total 5 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), done.
To https://github.com/huynp1999/huynp
   76b9764..31fa01c  master -> master
```
