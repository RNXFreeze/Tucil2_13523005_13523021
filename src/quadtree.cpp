/* Nama       : Muhammad Raihan Nazhim Oktana & Muhammad Alfansya */
/* NIM        : 13523021 & 13523005 - Teknik Informatika          */
/* Tanggal    : Jumat, 11 April 2025                              */
/* Tugas      : Stima (IF2211-24) - Tucil 2 - Divide & Conquer    */
/* File       : quadtree.cpp                                      */
/* Deskripsi  : F02B - Quadtree - Implementasi CPP                */
/* PJ F02B    : Muhammad Raihan Nazhim Oktana - 13523021          */

#include <bits/stdc++.h>
#include "quadtree.hpp"
using namespace std;

static double ComputeVariance(const vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , Pixel& average) {
    long long sumr = 0 , sumg = 0 , sumb = 0;
    long long n = (long long) blockw * blockh;
    for (int i = starty ; i < starty + blockh ; i++) {
        for (int j = startx ; j < startx + blockw ; j++) {
            sumr += image[i][j].r;
            sumg += image[i][j].g;
            sumb += image[i][j].b;
        }
    }
    double meanr = (double) sumr / n;
    double meang = (double) sumg / n;
    double meanb = (double) sumb / n;
    average.r = (unsigned char) round(meanr);
    average.g = (unsigned char) round(meang);
    average.b = (unsigned char) round(meanb);
    double varr = 0 , varg = 0 , varb = 0;
    for (int i = starty ; i < starty + blockh ; i++) {
        for (int j = startx ; j < startx + blockw ; j++) {
            double dr = image[i][j].r - meanr;
            double dg = image[i][j].g - meang;
            double db = image[i][j].b - meanb;
            varr += dr * dr;
            varg += dg * dg;
            varb += db * db;
        }
    }
    varr /= n;
    varg /= n;
    varb /= n;
    double res = (varr + varg + varb) / 3.0;
    return res;
}

static double ComputeMAD(const vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , Pixel& average) {
    long long sumr = 0 , sumg = 0 , sumb = 0;
    long long n = (long long) blockw * blockh;
    for (int i = starty ; i < starty + blockh ; i++) {
        for (int j = startx ; j < startx + blockw ; j++) {
            sumr += image[i][j].r;
            sumg += image[i][j].g;
            sumb += image[i][j].b;
        }
    }
    double meanr = (double) sumr / n;
    double meang = (double) sumg / n;
    double meanb = (double) sumb / n;
    average.r = (unsigned char) round(meanr);
    average.g = (unsigned char) round(meang);
    average.b = (unsigned char) round(meanb);
    double madr = 0 , madg = 0 , madb = 0;
    for (int i = starty ; i < starty + blockh ; i++) {
        for (int j = startx ; j < startx + blockw ; j++) {
            madr += fabs(image[i][j].r - meanr);
            madg += fabs(image[i][j].g - meang);
            madb += fabs(image[i][j].b - meanb);
        }
    }
    madr /= n;
    madg /= n;
    madb /= n;
    double res = (madr + madg + madb) / 3.0;
    return res;
}

static double ComputeMaxPixelDiff(const vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , Pixel& average) {
    int minr = 255 , ming = 255 , minb = 255;
    int maxr = 0 , maxg = 0 , maxb = 0;
    long long sumr = 0 , sumg = 0 , sumb = 0;
    for (int i = starty ; i < starty + blockh ; i++) {
        for (int j = startx ; j < startx + blockw ; j++) {
            int r = image[i][j].r;
            int g = image[i][j].g;
            int b = image[i][j].b;
            maxr = max(maxr , r);
            minr = min(minr , r);
            maxg = max(maxg , g);
            ming = min(ming , g);
            maxb = max(maxb , b);
            minb = min(minb , b);
        }
    }
    double dr = (double) (maxr - minr);
    double dg = (double) (maxg - ming);
    double db = (double) (maxb - minb);
    double res = (dr + dg + db) / 3.0;
    return res;
}

static double ComputeEntropy(const vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , Pixel& average) {
    long long sumr = 0 , sumg = 0 , sumb = 0;
    long long n = (long long) blockw * blockh;
    for (int i = starty ; i < starty + blockh ; i++) {
        for (int j = startx ; j < startx + blockw ; j++) {
            sumr += image[i][j].r;
            sumg += image[i][j].g;
            sumb += image[i][j].b;
        }
    }
    double meanr = (double) sumr / n;
    double meang = (double) sumg / n;
    double meanb = (double) sumb / n;
    average.r = (unsigned char) round(meanr);
    average.g = (unsigned char) round(meang);
    average.b = (unsigned char) round(meanb);
    vector<int> vhistr(256 , 0) , vhistg(256 , 0) , vhistb(256 , 0);
    for (int i = starty ; i < starty + blockh ; i++) {
        for (int j = startx ; j < startx + blockw ; j++) {
            vhistr[image[i][j].r]++;
            vhistg[image[i][j].g]++;
            vhistb[image[i][j].b]++;
        }
    }
    auto solve_entropy = [&](const vector<int>& hist) {
        double e = 0.0;
        for (int i = 0 ; i < 256 ; i++) {
            if (hist[i] > 0) {
                double p = (double) hist[i] / n;
                e += -p * log2(p);
            }
        }
        return e;
    };
    double er = solve_entropy(vhistr);
    double eg = solve_entropy(vhistg);
    double eb = solve_entropy(vhistb);
    double res = (er + eg + eb) / 3.0;
    return res;
}

double ComputeBlockError(const vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , int method , Pixel& average) {
    if (method == 1) {
        return ComputeVariance(image , startx , starty , blockw , blockh , average);
    } else if (method == 2) {
        return ComputeMAD(image , startx , starty , blockw , blockh , average);
    } else if (method == 3) {
        return ComputeMaxPixelDiff(image , startx , starty , blockw , blockh , average);
    } else if (method == 4) {
        return ComputeEntropy(image , startx , starty , blockw , blockh , average);
    } else {
        return ComputeVariance(image , startx , starty , blockw , blockh , average);
    }
}

QuadNode* BuildQuadTree(vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , int min_block_size , double threshold , int method) {
    QuadNode* node = new QuadNode();
    (*node).startx = startx;
    (*node).starty = starty;
    (*node).blockw = blockw;
    (*node).blockh = blockh;
    Pixel avg;
    double errVal = ComputeBlockError(image , startx , starty , blockw , blockh , method , avg);
    (*node).avg_color = avg;
    if ((errVal > threshold) && (blockw > min_block_size) && (blockh > min_block_size)) {
        int halfW = blockw / 2;
        int halfH = blockh / 2;
        (*node).child[0] = BuildQuadTree(image , startx , starty , halfW , halfH , min_block_size , threshold , method);
        (*node).child[1] = BuildQuadTree(image , startx + halfW , starty , blockw - halfW , halfH , min_block_size , threshold , method);
        (*node).child[2] = BuildQuadTree(image , startx , starty + halfH , halfW , blockh - halfH , min_block_size , threshold , method);
        (*node).child[3] = BuildQuadTree(image , startx + halfW , starty + halfH , blockw - halfW , blockh - halfH , min_block_size , threshold , method);
    }
    return node;
}

void ReconstructQuadTree(QuadNode* root , vector<vector<Pixel>>& res_img) {
    if (root) {
        bool check_leaf = true;
        for (int i = 0 ; i < 4 ; i++) {
            if ((*root).child[i] != nullptr) {
                check_leaf = false;
                break;
            }
        }
        if (check_leaf) {
            for (int i = (*root).starty ; i < (*root).starty + (*root).blockh ; i++) {
                for (int j = (*root).startx ; j < (*root).startx + (*root).blockw ; j++) {
                    res_img[i][j] = (*root).avg_color;
                }
            }
        } else {
            for (int i = 0 ; i < 4 ; i++) {
                ReconstructQuadTree((*root).child[i] , res_img);
            }
        }
    }
}

void FreeQuadTree(QuadNode* root) {
    if (root) {
        for (int i = 0 ; i < 4 ; i++) {
            FreeQuadTree((*root).child[i]);
        }
        delete root;
    }
}

void GetQuadTreeInfo(QuadNode* root , int& node_count , int& max_depth , int cur_depth) {
    if (root) {
        node_count++;
        if (cur_depth > max_depth) {
            max_depth = cur_depth;
        }
        for (int i = 0 ; i < 4 ; i++) {
            if ((*root).child[i]) {
                GetQuadTreeInfo((*root).child[i] , node_count , max_depth , cur_depth + 1);
            }
        }
    }
}