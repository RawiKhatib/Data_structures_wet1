#pragma once
#include <iostream>
#include "exceptions.h"
#include "AvlTree.h" 

class horse;

class herd{
    private:
        const int herdId;
        int num_of_horses ;
        AVLTree<horse, int> herd_horses_tree;

    public:  
        herd(int herdId);
         int get_herdId() const;
        int get_num_of_horses() const;
        void set_num_of_horses(int newNumber);
        horse* get_first_horse() const;
        void set_first_horse(horse *horse);
        bool get_circle_horse() const;
        void set_circle_horse(bool newResult)  ;
        AVLTree<horse, int>& get_herd_horse_tree() ;
        

        herd& operator=(const herd& other);
        herd(const herd& other) = default;
        
};


        int herdIdKeyFn(const herd& herd);
//add horse dec :

class horse {
    private:
        const int horseId;
        const int speed;
        horse* Horse_to_follow;
        herd* horse_herd;  // Pointer to herd
        bool visited ; 
        int version ; 
        bool is_follow_here ; 

    public:
        // Constructor declaration
        horse(const int horseId, const int speed);

        // Getters for Horse attributes
        const int get_HorseId() const;
        const int get_speed() const;
        herd* get_horse_herd() const;
        horse* get_prev_Horse() const;
        horse* get_Horse_to_follow() const;

        bool set_Horse_to_follow(horse* horse);
        bool set_prev_horse(horse* horse);
        void set_horse_herd(herd* herd);

        // Change the horse this one follows
        bool change_follow(horse* newFollow);
        bool get_visited() const ; 
        void set_visited(bool L) ; 
        int get_version() const ; 
        void set_version(int amount ); 
        bool get_is_follow_here() const ; 
        void set_is_follow_here(bool K) ; 

};

        int horseIdKeyFn(const horse& h);

