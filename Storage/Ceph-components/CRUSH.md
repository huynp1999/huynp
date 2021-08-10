# Thuật toán CRUSH
Có 2 cách để truy xuất dữ liệu từ một ổ cứng

1. Metadata server: thông qua metadata server làm trung gian, tại đây sẽ lưu giữ và theo dõi thông tin về các dữ liệu để từ đó chỉ ra đường dẫn lưu trữ của chúng. Với quy mổ nhỏ, độ trễ có thể là không đáng kể nhưng đối với hệ thống storage lớn thì độ trễ là rất cao, hạn chế sự mở rộng.

<img src="https://user-images.githubusercontent.com/83684068/128806396-022ce781-cbee-4da6-9dfb-dc7f3eaf614e.png" alt="drawing" width="550"/>

2. Phân chia cluster theo keyword, tuy nhiên phương pháp này không khả khi đối với hệ thống lớn và bất định

<img src="https://user-images.githubusercontent.com/83684068/128806608-636fd749-72c5-436d-8533-d0b6061a7209.png" alt="drawing" width="550"/>

3. CRUSH: Ceph sử dụng phương pháp khác hoàn toàn gọi là CRUSH, theo đó các dữ liệu khi lưu trữ trong cluster sẽ được băm (hashing) và chia vào các PG (placement group) khác nhau.
Và như vậy thuật toán CRUSH sẽ dựa trên yêu cầu, tính toán vị trí data nên được ghi và đọc ở đâu dựa trên 3 yêu tố là PG, cluster state và rule set được monitor đưa ra. Tốc độ truy xuất tổng cũng sẽ được cải thiện hơn.

<img src="https://user-images.githubusercontent.com/83684068/128807418-d8a259e0-e00b-4583-a275-0cd5643e3aea.png" alt="drawing" width="550"/>

Trong trường hợp có lỗi xảy trong một node, các monitor sẽ thực hiện vote để xác nhận node này đã bị down ([PASOX](./PASOX.md) và cập nhật cluster map mới. OSD khi nhận diện được sẽ replicate dữ liệu bị mất từ các node còn sống và tái cân bằng lại cluster. 

<img src="https://user-images.githubusercontent.com/83684068/128808064-d382ba33-f95c-4aa9-8128-56c6022a71a1.png" alt="drawing" width="550"/>
