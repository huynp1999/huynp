# Thuật toán PAXOS
Trong một mạng lưới, để đánh giá như nào là một tiến trình lỗi cần dựa trên kết quả đánh giá của đa số các tiến trình khác.
PAXOS ra đời nhằm giải quyết quá trình đánh giá này.
Một tiến trình được coi là lỗi khi có nhiều hơn một nửa các tiến trình công nhận (lý do có thể do mất kết nối, không hoạt động, v.v)

## Các định nghĩa
Có 3 role mà các tiến trình (process) có thể có:
- `proposer`: là process đề xuất các giá trị. Đa số thời gian, chỉ có một process đóng vai trò `proposer`, như vậy cũng được gọi là leader
- `acceptor`: `acceptor` có thể accept các giá trị đề xuất. Một tập hợp các acceptor được gọi là quorum. Khi một đề xuất đã được chấp nhận bởi quorum, có nghĩa là đề xuất này đã được chọn.
- `learner`: sau khi đề xuất được chọn, `proposer` thông báo giá trị đến xuất đến cho các process, các process đó được gọi là `learner`.

## Giải quyết với 3 node mon trong Ceph
Trong ví dụ này là cách xử lý vote của 3 monitor khi một OSD bị down và đề xuất theo một giá trị nhãn đại diện `N` duy nhất. Nhãn cũng là các số tự nhiên được sử dụng để sắp xếp các đề xuất. (vậy một monitor đề xuất OSD bị down khi nào thì có thể xem tại [đây](https://docs.ceph.com/en/latest/rados/configuration/mon-osd-interaction/))

Cụ thể hơn, có 3 node monitor trong đó:
- node 1 sẽ đóng vai trò làm proposer đề xuất việc "OSD_1 đã bị down" với giá trị đại diện N=42
- node 2, 3 còn lại đóng vai trò acceptor

![image](https://user-images.githubusercontent.com/83684068/128969421-5f1ec787-2ea7-4811-a9ff-fdc763822b9f.png)

Pha 1, chuẩn bị:
- proposer: chọn một số duy nhất và quảng bá yêu cầu với nhãn N chuẩn bị cho acceptors.
- acceptor: Khi một acceptor nhận một yêu cầu chuẩn bị với nhãn N sẽ xảy ra 2 trường hợp
  - NACK: acceptor sẽ bỏ qua nếu nó đã nhận được yêu cầu chuẩn bị với nhãn cao hơn.
  - ACK: Ngược lại, acceptor sẽ chấp nhận đề xuất và không không nhận bất kỳ yêu cầu nào có nhãn thấp hơn kể từ bây giờ.

Pha 2, đồng ý:

Trong pha này có 3 trường hợp xảy ra:
- 2 acceptor đều đồng ý: khi cả 2 acceptor đều đồng ý nhận đề xuất, proposer để đưa ra để xuất và cả 3 node cùng thống nhất "OSD_1 đã bị down"
- 1 acceptor đồng ý: ví dụ node 3 từ chối đề xuất, lúc này chỉ còn 2 acceptor là node 1 và node 2 (bản thân prososer cũng chính là 1 acceptor), và do có số vote đồng thuận cao hơn (2>1) nên đề xuất vẫn được thông qua "OSD_1 đã bị down"
- 0 acceptor đồng ý: khi cả node 2 và 3 đều từ chối đề xuất, số vote không đồng thuận lúc này lớn hơn. Và như vậy, đề xuất không được thông qua, OSD_1 vẫn được coi như đang up
