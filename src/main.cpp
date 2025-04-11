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
    bool check = false;
    string input_path , lower_input;
    int width , height;
    vector<vector<Pixel>> input_image;
    auto str_ends_with = [](const string& str , const string& sfx) -> bool {
        return str.size() >= sfx.size() && str.compare(str.size() - sfx.size() , sfx.size() , sfx) == 0;
    };
    cout << "Masukkan path gambar yang akan dikompresi (JPG / JPEG / PNG) : ";
    getline(cin , input_path);
    while (!check) {
        lower_input = input_path;
        transform(lower_input.begin() , lower_input.end() , lower_input.begin() , ::tolower);
        while (!(str_ends_with(lower_input , ".jpg") || str_ends_with(lower_input , ".jpeg") || str_ends_with(lower_input , ".png"))) {
            cout << "Error : File input harus bertipe .jpg / .jpeg / .png" << endl;
            cout << "[RE] Masukkan path gambar yang akan dikompresi (JPG / JPEG / PNG) : ";
            getline(cin , input_path);
            lower_input = input_path;
            transform(lower_input.begin() , lower_input.end() , lower_input.begin() , ::tolower);
        }
        check = load_image(input_path , input_image , width , height);
        if (!check) {
            cout << "Error : Gagal load gambar. Pastikan file tersedia, aman, dan path sesuai." << endl;
            cout << "[RE] Masukkan path gambar yang akan dikompresi (JPG / JPEG / PNG) : ";
            getline(cin , input_path);
        }
    }
    cout << "---------------------------------------------" << endl;
    cout << "Pilihan Metode Perhitungan Error :" << endl;
    cout << "1. Variance" << endl;
    cout << "2. Mean Absolute Deviation (MAD)" << endl;
    cout << "3. Max Pixel Difference" << endl;
    cout << "4. Entropy" << endl;
    cout << "5. Structural Similarity Index (SSIM)" << endl;
    cout << "Masukkan metode yang ingin digunakan (angka) : ";
    int method;
    cin >> method;
    while (method < 1 || method > 4) {
        cout << "Error : Metode tidak valid. Hanya boleh 1 - 4 (SSIM belum tersedia)." << endl;
        cout << "[RE] Masukkan metode yang ingin digunakan (angka) : ";
        cin >> method;
    }
    cout << "---------------------------------------------" << endl;
    if (method == 1) {
        cout << "Saran Range Threshold Metode Variance : 0 <= ... <= 10000" << endl;
    } else if (method == 2) {
        cout << "Saran Range Threshold Metode MAD : 0 <= ... <= 255" << endl;
    } else if (method == 3) {
        cout << "Saran Range Threshold Metode MaxPixelDiff : 0 <= ... <= 765" << endl;
    } else if (method == 4) {
        cout << "Saran Range Threshold Metode Entropy : 0 <= ... <= 24" << endl;
    } else {
        cout << "Saran Range Threshold Metode SSIM : 0 <= ... <= 1" << endl;
    }
    cout << "Masukkan nilai threshold (ambang batas) : ";
    double threshold;
    cin >> threshold;
    while (threshold < 0) {
        cout << "Error : Threshold tidak valid. Threshold tidak boleh negatif, usahakan sesuai saran." << endl;
        cout << "[RE] Masukkan nilai threshold (ambang batas) : ";
        cin >> threshold;
    }
    cout << "---------------------------------------------" << endl;
    cout << "Masukkan minimum block size yang diinginkan (panjang sisi) : ";
    int min_block_size;
    cin >> min_block_size;
    while (min_block_size < 1 || min_block_size > min(width , height)) {
        cout << "Error : Ukuran tidak valid. Hanya boleh 1 - " << min(width , height) << endl;
        cout << "[RE] Masukkan minimum block size yang diinginkan (panjang sisi) : ";
        cin >> min_block_size;
    }
    cout << "---------------------------------------------" << endl;
    cout << "Masukkan target persentase kompresi (masukkan 0 untuk menonaktifkan) : ";
    double target_compression;
    cin >> target_compression;
    while (target_compression < 0.0 || target_compression > 1.0) {
        cout << "Error : Target kompresi tidak valid. Hanya boleh 0.0 < ... < 1.0." << endl;
        cout << "[RE] Masukkan target persentase kompresi (masukkan 0 untuk menonaktifkan) : ";
        cin >> target_compression;
    }
    cin.ignore();
    cout << "---------------------------------------------" << endl;
    cout << "Masukkan output path gambar hasil kompresi (PNG) : ";
    string output_path;
    getline(cin , output_path);
    lower_input = output_path;
    transform(lower_input.begin() , lower_input.end() , lower_input.begin() , ::tolower);
    while (!(str_ends_with(lower_input , ".png"))) {
        cout << "Error : File output harus bertipe .png" << endl;
        cout << "[RE] Masukkan output path gambar hasil kompresi (PNG) : ";
        getline(cin , output_path);
        lower_input = output_path;
        transform(lower_input.begin() , lower_input.end() , lower_input.begin() , ::tolower);
    }
    cout << "---------------------------------------------" << endl;
    cout << "Masukkan path output GIF (enter untuk menonaktifkan) : ";
    string gif_path;
    getline(cin , gif_path);
    lower_input = gif_path;
    transform(lower_input.begin() , lower_input.end() , lower_input.begin() , ::tolower);
    while (!gif_path.empty() && !str_ends_with(lower_input , ".gif")) {
        cout << "Error : File output harus bertipe .gif" << endl;
        cout << "[RE] Masukkan path output GIF (enter untuk menonaktifkan) : ";
        getline(cin , gif_path);
        lower_input = gif_path;
        transform(lower_input.begin() , lower_input.end() , lower_input.begin() , ::tolower);
    }
    cout << "---------------------------------------------" << endl;
    cout << "Loading..." << endl;
    auto start = chrono::high_resolution_clock::now();
    int original_size = size_of_file(input_path);
    if (target_compression > 0.0) {
        double mint = 0.0 , maxt = 10000.0;
        if (method == 1) {
            mint = 0.0;
            maxt = 10000.0;
        } else if (method == 2) {
            mint = 0.0;
            maxt = 255.0;
        } else if (method == 3) {
            mint = 0.0;
            maxt = 765.0;
        } else if (method == 4) {
            mint = 0.0;
            maxt = 24.0;
        } else {
            mint = 0.0;
            maxt = 1.0;
        }
        int best_final_size = 0;
        double tolerance_ratio = 0.0005;
        double best_threshold = threshold;
        double best_diff = std::numeric_limits<double>::max();
        for (int k = 0 ; k < 20 ; k++) {
            double mid = (mint + maxt) / 2;
            QuadNode* temp_root = BuildQuadTree(input_image , 0 , 0 , width , height , min_block_size , mid , method);
            vector<vector<Pixel>> temp_image(height , vector<Pixel> (width));
            for (int i = 0 ; i < height ; i++) {
                for (int j = 0 ; j < width ; j++) {
                    temp_image[i][j] = input_image[i][j];
                }
            }
            ReconstructQuadTree(temp_root , temp_image);
            FreeQuadTree(temp_root);
            string str_out = "temp_image.png";
            check = save_image(str_out , temp_image , width , height);
            int temp_size = size_of_file(str_out);
            double ratio = fabs(1.0 - ((double) temp_size / (double) original_size));
            double diff = fabs(ratio - target_compression);
            if (diff < best_diff) {
                best_diff = diff;
                best_threshold = mid;
                best_final_size = temp_size;
            }
            if (ratio < target_compression) {
                mint = mid;
            } else {
                maxt = mid;
            }
            cout << "\r                                                                          \r" << flush;
            cout << "[COMPRESSING - " << k + 1 << "] :: " << fixed << setprecision(3) << ratio * 100 << "% :: Threshold " << fixed << setprecision(3) << best_threshold << flush;
            if (best_diff < tolerance_ratio || fabs(maxt - mint) < 0.000001 || k == 19) {
                cout << endl << "[Threshold Akhir]      : " << fixed << setprecision(3) << best_threshold << endl;
                cout << "Loading..." << endl;
                break;
            }
        }
        threshold = best_threshold;
        remove("./temp_image.png");
    }
    QuadNode* root = BuildQuadTree(input_image , 0 , 0 , width , height , min_block_size , threshold , method);
    vector<vector<Pixel>> res_image(height , vector<Pixel> (width));
    for (int i = 0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            res_image[i][j] = input_image[i][j];
        }
    }
    ReconstructQuadTree(root , res_image);
    bool saved = save_image(output_path , res_image , width , height);
    if (!saved) {
        cout << "Error : Gagal Save Gambar." << endl;
        cout << "Output Path : " << output_path << endl;
    } else {
        int node_count = 0 , max_depth = 0;
        GetQuadTreeInfo(root , node_count , max_depth , 1);
        FreeQuadTree(root);
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
    cout << "=================================================" << endl;
    cout << "    TERIMA KASIH TELAH MENGGUNAKAN PROGRAM INI   " << endl;
    cout << "              SAMPAI JUMPA KEMBALI!              " << endl;
    cout << "=================================================" << endl;
}