#pragma once
#include <iostream>
#include "exceptions.h"
#include "AvlTree.h"
#include <memory>
using namespace std;

class horse;

class herd{
private:
    const int herdId;
    int num_of_horses ;
    AVLTree<shared_ptr<horse>, int> herd_horses_tree;

public:
    herd(int herdId);
    int get_herdId() const;
    int get_num_of_horses() const;
    void set_num_of_horses(int newNumber);
    shared_ptr<horse> get_first_horse() const;
//    void set_first_horse(horse *horse);
    bool get_circle_horse() const;
    void set_circle_horse(bool newResult)  ;
    AVLTree<shared_ptr<horse>, int>& get_herd_horse_tree() ;


    herd& operator=(const herd& other);
    herd(const herd& other) = default;

};



//add horse dec :

class horse {
private:
    const int horseId;
    const int speed;
    shared_ptr<horse> Horse_to_follow;
    shared_ptr<herd> horse_herd;  // Pointer to herd
    bool visited ;
    int version ;
    bool is_follow_here ;

public:
    // Constructor declaration
    horse(const int horseId, const int speed);

    // Getters for Horse attributes
    const int get_HorseId() const;
    const int get_speed() const;
    shared_ptr<herd> get_horse_herd() const;
    shared_ptr<horse> get_prev_Horse() const;
    shared_ptr<horse> get_Horse_to_follow()   ;

    bool set_Horse_to_follow(shared_ptr<horse> horse);
    bool set_prev_horse(shared_ptr<horse> horse);
    void set_horse_herd(shared_ptr<herd> herd);

    // Change the horse this one follows
    bool change_follow(shared_ptr<horse> newFollow);
    bool get_visited() const ;
    void set_visited(bool value)  ;
    int get_version()  ;
    void set_version(int amount );
    bool get_is_follow_here()  ;
    void set_is_follow_here(bool K) ;

};

int herdIdKeyFn(const shared_ptr<herd> &herd) ;


int horseIdKeyFn(const shared_ptr<horse> &h);



