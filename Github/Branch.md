# Branch
Dùng để quản lý các phiên bản, chức năng, hướng phát triển của một project. Đồng thời vẫn tiếp tục phát triển song song với đó.
Khi tiến hành commit lần đầu trong repository, Git sẽ tạo ra một branch có tên là master. Những lần commit sau sẽ được thêm vào branch master cho đến khi chuyển đổi branch.
## Ưu điểm
- Có thể thêm nhiều nhánh phát triển mới mà không bị ảnh hưởng tới nhau
- Có thể tạo nhiều development branch khác nhau mà sau này có thể hợp nhất lại (merge).
- Truy vết sửa đổi thông qua phần lịch sử giúp đưa biện pháp khắc phục dễ hơn

## Tạo branch
Có hai nhánh để tạo branch là master và develop. Các tính năng mới sẽ nằm trên nhánh develop, còn nhánh master chứa các bản sửa lỗi.
**ví dụ muốn tạo 1 branch từ branch develop có sẵn**
1. `git checkout develop`: chuyển tới branch cần tạo mới từ nó
2. `git checkout -b feature_1 develop`:tạo và chuyển tới branch mới tạo
3. `git push origin feature_1`: đẩy file được add trong index vào branch feature_1 vừa tạo

## Xoá branch
Trước tiên xoá (-d) branch tại máy mình và đẩy cập nhật lên 
1. `git branch -d develop_1`
2. `git push origin -d develop_1`

## Merge branch
Hợp nhất feature hoặc hotfix vào master
1. `git checkout master`: trước tiên cần phải quay trở về master branch
2. `git merge [branch]`: hợp nhất branch vào master


## Khác
- `git branch -a`: danh sách branch
