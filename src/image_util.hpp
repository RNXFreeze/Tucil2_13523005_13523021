/* Nama       : Muhammad Raihan Nazhim Oktana & Muhammad Alfansya */
/* NIM        : 13523021 & 13523005 - Teknik Informatika          */
/* Tanggal    : Jumat, 11 April 2025                              */
/* Tugas      : Stima (IF2211-24) - Tucil 2 - Divide & Conquer    */
/* File       : image_util.hpp                                    */
/* Deskripsi  : F03A - Image Utility - Header HPP                 */
/* PJ F03A    : Muhammad Alfansya - 13523005                      */

#ifndef IMAGE_UTIL_HPP
#define IMAGE_UTIL_HPP

#include <bits/stdc++.h>
#include <sys/stat.h>
using namespace std;

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

bool load_image(const string& filename , vector<vector<Pixel>>& image_data , int& width , int& height);
bool save_image(const string& filename , const vector<vector<Pixel>>& image_data , int width , int height);
int size_of_file(string file_path);

#endif