/* Nama       : Muhammad Raihan Nazhim Oktana & Muhammad Alfansya */
/* NIM        : 13523021 & 13523005 - Teknik Informatika          */
/* Tanggal    : Jumat, 11 April 2025                              */
/* Tugas      : Stima (IF2211-24) - Tucil 2 - Divide & Conquer    */
/* File       : image_util.cpp                                    */
/* Deskripsi  : F03B - Image Utility - Implementasi CPP           */
/* PJ F03B    : Muhammad Alfansya - 13523005                      */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <bits/stdc++.h>
#include "image_util.hpp"
using namespace std;

bool load_image(const string& filename , vector<vector<Pixel>>& image_data , int& width , int& height) {
    int channels;
    unsigned char* data = stbi_load(filename.c_str() , &width , &height , &channels , 3);
    if (!data) {
        return false;
    } else {
        image_data.resize(height , vector<Pixel> (width));
        size_t idx = 0;
        for (int i = 0 ; i < height ; i++) {
            for (int j = 0 ; j < width ; j++) {
                Pixel p;
                p.r = data[idx];
                p.g = data[idx + 1];
                p.b = data[idx + 2];
                image_data[i][j] = p;
                idx += 3;
            }
        }
        stbi_image_free(data);
        return true;
    }
}

bool save_image(const string& filename , const vector<vector<Pixel>>& image_data , int width , int height) {
    vector<unsigned char> buf(width * height * 3);
    size_t idx = 0 ;
    for (int i = 0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            buf[idx] = image_data[i][j].r;
            buf[idx + 1] = image_data[i][j].g;
            buf[idx + 2] = image_data[i][j].b;
            idx += 3;
        }
    }
    int stride_in_bytes = width * 3;
    if (!stbi_write_png(filename.c_str() , width , height , 3 , buf.data() , stride_in_bytes)) {
        return false;
    } else {
        return true;
    }
}

int size_of_file(string file_path) {
    struct stat file_info;
    int res = stat(file_path.c_str() , &file_info);
    if (res == 0) {
        long file_size = file_info.st_size;
        return ceil((double) file_size/1024);
    } else {
        return -1;
    }
}