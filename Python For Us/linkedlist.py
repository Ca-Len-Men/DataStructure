from typing import Generic, TypeVar


class __Node:
    def __init__(self, data=None):
        global __NULL
        self.data = data
        self.left = __NULL
        self.right = __NULL

    def ref_left(self, other):
        self.left = other
        other.right = self

    def ref_right(self, other):
        self.right = other
        other.left = self


__NULL = __Node()       # __NULL : mặc định là nút kết thúc ( xem nó như None )
_T = TypeVar('_T')


class DLList(Generic[_T]):
    class DLLPointer(Generic[_T]):
        # Lớp này do Anh Quan

        def __init__(self, dlist, node):
            self._node = node       # _node : tham chiếu đến một nút
            self._dlist = dlist     # _dlist : tham chiếu đến double list

        @property
        def value(self) -> _T:
            # Trả về giá trị tại nút nó tham chiếu đến
            pass

        @value.setter   # type: ignore
        def value(self, _: _T) -> None:
            # Gán giá trị cho nút nó tham chiếu đến
            pass

        def next(self, n=1) -> bool:
            # Đi qua n nút tiếp theo
            pass

        def prev(self, n: int) -> bool:
            # Đi qua n nút trước đó
            pass

        def remove_next(self) -> bool:
            # Xóa nút liền sau
            pass

        def remove_prev(self) -> bool:
            # Xóa nút liền trước
            pass

        def __str__(self) -> str:
            return f'<class DLList.DLLPointer with value = {self._node.data}>'

        def __next__(self) -> _T:
            # Trả về giá trị tại nút đang tham chiếu và đi đến nút kế tiếp
            pass

    def __init__(self, iterable=None):
        # Hàm này do Long
        # Khởi tạo DLList, nếu iterable khác None -> lấy dữ liệu đưa vào list.
        # Các attributes :
        #                   self._head
        #                   self._tail
        #                   self._size
        pass

    def push_front(self, element):
        # Hàm này do Nghiep Tran
        # Thêm phần tử vào đầu danh sách
        pass

    def push_back(self, element) -> None:
        # Hàm này do Notch Apple
        # Thêm phần tử vào cuối danh sách
        pass

    def pop_front(self) -> _T:
        # Hàm này do Tran Ngoc
        # Lấy ra phần tử ở đầu danh sách
        pass

    def pop_back(self) -> _T:
        # Hàm này do Long
        # Lấy ra phần tử ở cuối danh sách
        pass

    def reverse(self) -> None:
        # Hàm này do Nghiep Tran
        # Đảo danh sách
        pass

    def clear(self) -> None:
        # Hàm này do Anh Quan
        # Xóa toàn bộ danh sách
        pass

    def __len__(self) -> int:
        # Hàm này do Tran Ngoc
        pass

    def __str__(self) -> str:
        # Hàm này do Notch Apple
        # In danh sách theo định dạng : DLList<[1, 2, 3]>
        pass

    def __repr__(self) -> str:
        return self.__str__()
