/* Nama       : Muhammad Raihan Nazhim Oktana & Muhammad Alfansya */
/* NIM        : 13523021 & 13523005 - Teknik Informatika          */
/* Tanggal    : Jumat, 11 April 2025                              */
/* Tugas      : Stima (IF2211-24) - Tucil 2 - Divide & Conquer    */
/* File       : main.cpp                                          */
/* Deskripsi  : F01 - Main - File Main Program CPP                */
/* PJ F01     : Muhammad Alfansya - 13523005                      */

#include <bits/stdc++.h>
#include "quadtree.hpp"
#include "image_util.hpp"
using namespace std;

int main() {
    cout << "=============================================" << endl;
    cout << "  SELAMAT DATANG DI PROGRAM KOMPRESI GAMBAR  " << endl;
    cout << "        QUADTREE BY RAIHAN & ALFANSYA        " << endl;
    cout << "             13523021 & 13523005             " << endl;
    cout << "=============================================" << endl;
    cout << "Masukkan path gambar yang akan dikompresi (JPG / JPEG / PNG) : ";
    string input_path;
    getline(cin , input_path);
    cout << "Pilihan Metode Perhitungan Error :" << endl;
    cout << "1. Variance" << endl;
    cout << "2. Mean Absolute Deviation (MAD)" << endl;
    cout << "3. Max Pixel Difference" << endl;
    cout << "4. Entropy" << endl;
    cout << "5. SSIM (dalam pengembangan)" << endl;
    cout << "Masukkan metode yang ingin digunakan (angka) : ";
    int method;
    cin >> method;
    cout << "Masukkan nilai threshold (ambang batas) : ";
    double threshold;
    cin >> threshold;
    cout << "Masukkan minimum block size yang diinginkan : ";
    int min_block_size;
    cin >> min_block_size;
    cout << "Masukkan target persentase kompresi (masukkan 0 untuk menonaktifkan) : ";
    double target_compression;
    cin >> target_compression;
    target_compression = 0.0;
    cin.ignore();
    cout << "Masukkan output path gambar hasil kompresi (PNG) : ";
    string output_path;
    getline(cin , output_path);
    cout << "Masukkan path output GIF (enter untuk menonaktifkan) : ";
    string gif_path;
    getline(cin , gif_path);
    int width , height;
    vector<vector<Pixel>> image;
    bool check = load_image(input_path , image , width , height);
    if (!check) {
        cout << "Error : Gagal Load Gambar." << endl;
        cout << "Input Path : " << input_path << endl;
    } else {
        auto start = chrono::high_resolution_clock::now();
        QuadNode* root = BuildQuadTree(image , 0 , 0 , width , height , min_block_size , threshold , method);
        vector<vector<Pixel>> res_img(height , vector<Pixel> (width));
        for (int i = 0 ; i < height ; i++) {
            for (int j = 0 ; j < width ; j++) {
                res_img[i][j] = image[i][j];
            }
        }
        ReconstructQuadTree(root , res_img);
        bool saved = save_image(output_path , res_img , width , height);
        if (!saved) {
            cout << "Error : Gagal Save Gambar." << endl;
            cout << "Output Path : " << output_path << endl;
        } else {
            int node_count = 0 , max_depth = 0;
            GetQuadTreeInfo(root , node_count , max_depth);
            FreeQuadTree(root);
            int original_size = size_of_file(input_path);
            int final_size = size_of_file(output_path);
            double compression_ratio = (1.0 - ((double) final_size / (double) original_size)) * 100.0;
            auto end = chrono::high_resolution_clock::now();
            int time = chrono::duration<double, std::milli>(end - start).count();
            cout << "=================== SUKSES ======================" << endl;
            cout << "[Waktu Eksekusi]       : " << time << " ms" << endl;
            cout << "[Ukuran Gambar Awal]   : " << original_size << " kb" << endl;
            cout << "[Ukuran Gambar Akhir]  : " << final_size << " kb" << endl;
            cout << "[Persentase Kompresi]  : " << fixed << setprecision(3) << compression_ratio << "%" << endl;
            cout << "[Kedalaman Tree]       : " << max_depth << " depth" << endl;
            cout << "[Banyak Tree Node]     : " << node_count << " node" << endl;
            cout << "[Output File Path PNG] : " << output_path << endl;
            cout << "[Output File Path GIF] : " << "N/A" << endl;
        }
    }
    cout << "=================================================" << endl;
    cout << "    TERIMA KASIH TELAH MENGGUNAKAN PROGRAM INI   " << endl;
    cout << "              SAMPAI JUMPA KEMBALI!              " << endl;
    cout << "=================================================" << endl;
}