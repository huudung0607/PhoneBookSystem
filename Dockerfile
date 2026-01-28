FROM gcc:latest

WORKDIR /app

# Chỉ copy những gì chắc chắn tồn tại
COPY Source.cpp .

# Tạo file trống nếu chúng không được copy từ máy chủ
# Điều này đảm bảo app không bị crash khi đọc file rỗng
RUN touch UserList.txt ContactList.txt

# Nếu bạn muốn nạp dữ liệu có sẵn từ máy vào, hãy dùng lệnh copy đơn giản:
# COPY UserList.txt .
# (Nhưng dòng này sẽ báo lỗi nếu máy bạn không có file UserList.txt)

RUN g++ -o phonebook_app Source.cpp

CMD ["./phonebook_app"]