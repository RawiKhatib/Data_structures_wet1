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
    shared_ptr<AVLTree<shared_ptr<horse>, int>> herd_horses_tree;
    

public:
    herd(int herdId);
    int get_herdId() const;
    int get_num_of_horses() const;
    void set_num_of_horses(int newNumber);
    shared_ptr<horse> get_first_horse() const;
//    void set_first_horse(horse *horse);
    bool get_circle_horse() const;
    void set_circle_horse(bool newResult)  ;
    shared_ptr<AVLTree<shared_ptr<horse>, int>>  get_herd_horse_tree() ;


    herd& operator=(const herd& other);
    herd(const herd& other) = default;

};





class horse {
public:
    const int horseId;
    const int speed;
    weak_ptr<horse> Horse_to_follow;
    weak_ptr<herd> horse_herd;  // Pointer to herd
    bool visited ;
    int version ;
    int is_follow_here ;
    int insert_version ; 
    bool is_prev ; 

public:
    // Constructor declaration
    horse(const int horseId, const int speed);

    // Getters for Horse attributes
    const int get_HorseId() const;
    const int get_speed() const;
    weak_ptr<herd> get_horse_herd() const;
    shared_ptr<horse> get_prev_Horse() const;
    weak_ptr<horse> get_Horse_to_follow()   ;

    bool set_Horse_to_follow(shared_ptr<horse> horse);
    bool set_prev_horse(shared_ptr<horse> horse);
    void set_horse_herd(shared_ptr<herd> herd);

    // Change the horse this one follows
    bool change_follow(shared_ptr<horse> newFollow);
    bool get_visited() const ;
    void set_visited(bool value)  ;
    int get_version()  ;
    void set_version(int amount );
    int get_is_follow_here()  ;
    void set_is_follow_here(int K) ;

    int get_insert_version() const;
    void set_insert_version(int amount);

};

int herdIdKeyFn(const shared_ptr<herd> &herd) ;


int horseIdKeyFn(const shared_ptr<horse> &h);



