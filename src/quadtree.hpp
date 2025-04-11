/* Nama       : Muhammad Raihan Nazhim Oktana & Muhammad Alfansya */
/* NIM        : 13523021 & 13523005 - Teknik Informatika          */
/* Tanggal    : Jumat, 11 April 2025                              */
/* Tugas      : Stima (IF2211-24) - Tucil 2 - Divide & Conquer    */
/* File       : quadtree.hpp                                      */
/* Deskripsi  : F02A - Quadtree - Header HPP                      */
/* PJ F02A    : Muhammad Raihan Nazhim Oktana - 13523021          */

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <bits/stdc++.h>
#include "image_util.hpp"
using namespace std;

struct QuadNode {
    Pixel avg_color;
    int startx , starty;
    int blockw , blockh;
    QuadNode* child[4];
    QuadNode() {
        for (int i = 0 ; i < 4 ; i++) {
            child[i] = nullptr;
        }
    }
};

QuadNode* BuildQuadTree(vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , int min_block_size , double threshold , int method);
double ComputeBlockError(const vector<vector<Pixel>>& image , int startx , int starty , int blockw , int blockh , int method , Pixel& average);
void ReconstructQuadTree(QuadNode* root , vector<vector<Pixel>>& res_img);
void FreeQuadTree(QuadNode* root);
void GetQuadTreeInfo(QuadNode* root , int& node_count , int& max_depth , int cur_depth = 1);

#endif