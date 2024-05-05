// Image.cpp

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

// Default constructor
Image::Image() : Matrix(), filePath(""), numChannels(0), width(0), height(0) {}

Image::Image(const std::string& filePath) {
    // Load the image using stb_image
    int width, height, channels;
    uint8_t* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    // Initialize the Matrix info with the image data
    this->setRows(height);
    this->setColumns(width);
    this->width = width;
    this->height = height;
    this->filePath = filePath;
    this->numChannels = channels;
    this->data = Vector<Vector<uint8_t>>(height);

    //this is taken directly from the save method below.
    //if this is how it's accessed and then this is how its declared.
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        for (int k = 0; k < channels; k++) {
            //calculate rows and cols to pull image data from.
            this->data[i][j * channels + k] = imageData[(i * width + j) * channels + k];
        }
      }
    }
    // Free the loaded image data
    stbi_image_free(imageData);
}

// Constructor with file path, channels, width, and height
Image::Image(const std::string& filePath, int numChannels, int width, int height)
    : Matrix(height, width), filePath(filePath), numChannels(numChannels), width(width), height(height) {}

// Copy constructor
Image::Image(const Image& other) : Matrix(other.getHeight(), other.getWidth()), numChannels(other.getNumChannels()), filePath(other.getFilePath()) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (int k = 0; k < numChannels; k++) {
          //calculate rows and cols to pull image data from.
          //same access stratgey from the GIVEN save function...
          this->data[i][j * numChannels + k] = other[i][j * numChannels + k];
      }
    }
  }
}

// Assignment operator
Image& Image::operator=(const Image& other) {
    *this = Image(other);
    return *this;
}

// Destructor
Image::~Image() {
  //Since Matrix has a virtual destructor and this class extends Matrix
  //The matrix destructor will be called and clean up everything.
  //This class doesn't have any dynamically allocated variables to clean up.
}

// Scaling an image
Image Image::operator*(double scalar) const {
  if (scalar > 1 ) {
    std::cout << "Scalar is too high! Setting to 1." << std::endl;
    scalar = 1;
  }

  if (scalar < 0) {
    std::cout << "Scalar is too low! Setting to 0." << std::endl;
    scalar = 0;
  }

  for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
          for (int k = 0; k < numChannels; ++k) {
              this->data[i][j * numChannels + k] = scalar * this->data[i][j * numChannels + k];
          }
      }
  }
}

// Adding two images
Image Image::operator+(const Image& other) const {
  for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
          for (int k = 0; k < numChannels; ++k) {
              this->data[i][j * numChannels + k] = this->data[i][j * numChannels + k] + other.data[i][j * numChannels + k] > 255 ? 255 : this->data[i][j * numChannels + k] + other.data[i][j * numChannels + k];
          }
      }
  }
}

// Subtracting two images
Image Image::operator-(const Image& other) const {
  for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
          for (int k = 0; k < numChannels; ++k) {
              this->data[i][j * numChannels + k] = this->data[i][j * numChannels + k] - other.data[i][j * numChannels + k] < 0 ? 0 : this->data[i][j * numChannels + k] - other.data[i][j * numChannels + k];
          }
      }
  }
}

// Multiplying two images
Image Image::operator*(const Image& other) const {

    //Copied from Matrix * operator
    if (this->getCols() != other.getRows()) {
        std::cout << "Invalid Matrix dimensions for multiplication! Returning the first image." << std::endl;
        return *this;
    }

    int channels = this->getNumChannels();

    //Make a temporary vector of vectors
    Vector<Vector<uint8_t>> result = Vector<Vector<uint8_t>>(this->getRows());
    for (int i = 0; i < other.getCols(); i++) {
      result[i].resize(other.getCols());
    }

    // Initialize our result Vector<Vector> to 0
    for (int i = 0; i < this->getRows(); i++) {
      Vector<unsigned char> &row = result[i];
      for (int j = 0; i < other.getCols(); i++) {
        row[j] = 0;
      }
    }

    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        for (int k = 0; k < channels; k++) {
          //this formula is taken from online documentation of stb_image_resize...
          //it can be found on their github as this is how they access data from the
          //pointer interally within stb_image_resize.h
          for (int h = 0; h < this->getCols(); h++) {
            result[i][j * channels + k] += this->data[i][h * channels + k] * other[h][j * channels + k];
          }
        }
      }
    }

    //pull results from the temp matrix into the current Image
    for (int i = 0; i < this->getRows(); i++) {
        for (int j = 0; j < other.getCols(); j++) {
            for (int k = 0; k < channels; k++) {
                this->data[i][ j * channels + k] = result[i][j * channels + k];
            }
        }
    }

    for (int i = 0; this->getRows(); i++) {
      delete[] result[i].getElements();
    }


    return *this;

}


int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

int Image::getNumChannels() const {
    return numChannels;
}

std::string Image::getFilePath() const {
    return filePath;
}

void Image::save(const std::string& filePath) const {
    // Convert the Matrix data into a 1D array suitable for saving as an image
    std::vector<uint8_t> imageData;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < numChannels; ++k) {
                imageData.push_back(data[i][j * numChannels + k]);
            }
        }
    }

    // Save the image data to the specified file using stb_image_write
    stbi_write_png(filePath.c_str(), width, height, numChannels, imageData.data(), width * numChannels);
}

void Image::resize(int newWidth, int newHeight) {
  int width, height, channels;
  uint8_t* output;
  //easiest way to get the uint8_t data back
  uint8_t* imageData = stbi_load(
    filePath.c_str(),
    &width,
    &height,
    &channels,
    0
  );
  stbir_resize_uint8(
    imageData,
    this->getWidth(),
    this->getHeight(),
    0,
    output,
    newWidth,
    newHeight,
    0,
    3
  );

  this->width = newWidth;
  this->height = newHeight;
  this->setRows(this->height);
  this->setColumns(this->width);

  this->data = Vector<Vector<uint8_t>>(height);

  //this is taken directly from the save method below.
  //if this is how it's accessed and then this is how its declared.
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      for (int k = 0; k < channels; k++) {
          //this formula is taken from online documentation of stb_image_resize...
          //it can be found on their github as this is how they access data from the
          //pointer interally within stb_image_resize.h
          this->data[i][j * channels + k] = output[(i * width + j) * channels + k];
      }
    }
  }

  delete(imageData);
  delete(output);

}
