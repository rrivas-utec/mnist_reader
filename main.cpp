#include <iostream>
#include <fstream>
#include <bit>
#include <vector>

//"train-images.idx3-ubyte"

uint32_t to_big_endian(uint32_t value) {
  return ((value >> 24) & 0xff) |
         ((value << 8) & 0xff0000) |
         ((value >> 8) & 0xff00) |
         ((value << 24) & 0xff000000);
}

struct file_header_t {
  uint32_t magic{};
  uint32_t images{};
  uint32_t rows{};
  uint32_t columns{};
};

file_header_t convert_big_endian (const file_header_t& src) {
  return {
      to_big_endian(src.magic),
      to_big_endian(src.images),
      to_big_endian(src.rows),
      to_big_endian(src.columns)
  };
}

auto read(const std::string& file_name) {
  // read file
  std::fstream file(
      file_name,
      std::ios_base::in | std::ios_base::binary);
  // verify document
  if (!file.is_open()) {
    std::cout <<"Error: file not found\n";
  }
  // leyendo header
  file_header_t h;
  file.read((char*)(&h), sizeof(h));
  h = convert_big_endian(h);
  std::vector<std::vector<char>> images(
      h.images,
      std::vector<char>(h.rows * h.columns)
      );
  for (auto& img: images) {
    file.read(img.data(), h.rows * h.columns);
  }
  const auto& img = images[0];
  for (int i = 0; i < h.rows; ++i) {
    for (int j = 0; j < h.columns; ++j) {
      if (static_cast<unsigned>(img[i*h.columns + j]) > 0)
        std::cout << 1 << " ";
      else
        std::cout << ' ' << " ";
    }
    std::cout << std::endl;
  }
  return h;
}

int main() {
  auto h = read("train-images.idx3-ubyte");
  std::cout << h.rows << std::endl;
  std::cout << h.columns << std::endl;
  std::cout << h.images << std::endl;
  
  return 0;
}
