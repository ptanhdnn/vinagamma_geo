Source rod

- Khai báo thanh nguồn (nguồn + vỏ), đánh số cho từng thanh để khởi tạo beam random.
- Khai báo frame tương tự.
=> như vậy nguồn sẽ có tên đầy đủ là: "A_01_rodLVs".

- Tạo beam random.

Cụ thể
24/2:
- Đã khai báo xong source rod.
- Chưa định vị vị trí trong space để xác định physical position.
Solution: tạo lại kích thước và vị trí của các thanh nguồn trong generator.cc

3/5:
- Khai báo các thanh nguồn với các xác suất phát khác nhau dựa theo tỷ lệ hoạt độ của chúng.
- Khai báo các thanh ECB hoặc thay các thanh detector bằng vật liệu của ECB (khả thi).