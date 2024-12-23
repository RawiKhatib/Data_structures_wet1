
#include <iostream>
#include "exceptions.h"
#include "values.h"


        herd::herd(int herdId) : herdId(herdId) , num_of_horses(0) ,  herd_horses_tree(horseIdKeyFn)
        {
            if(herdId <= 0)
            {
               throw Invalid_Input();
            }
        }



         int herd::get_herdId() const
        {
            return this->herdId;
        }

        int herd::get_num_of_horses() const
        {
            return this->num_of_horses;
        }

        void herd::set_num_of_horses(int newNumber)
        {   
            this->num_of_horses =   newNumber;
        }

        AVLTree<horse, int>& herd::get_herd_horse_tree() {
            return this->herd_horses_tree ; 
        }

        horse::horse(const int horseId, const int speed)
        : horseId(horseId), speed(speed), Horse_to_follow(nullptr), horse_herd(nullptr) , visited(false)
        ,version(0) , is_follow_here(false)
        {
        if (horseId <= 0 || speed <= 0)
        {
            throw Invalid_Input();
        }
        }

        const int horse::get_HorseId() const
        {
            return this->horseId;
        }

        const int horse::get_speed() const
        {
            return this->speed;
        }

        herd* horse::get_horse_herd() const
        {
            return this->horse_herd;
        }

        bool horse::change_follow(horse* newFollow)
        {
            if(newFollow->get_HorseId() == Horse_to_follow->get_HorseId())
            {
                return false ; 
            }
            if(newFollow->get_horse_herd() != this->get_horse_herd())
            {
               return false ; 
            }

            if(newFollow == horse_herd->get_first_horse())
            {
                horse_herd->set_first_horse(this) ;
            }
            this->Horse_to_follow = newFollow;
            return true ; 
        }

        horse* horse::get_Horse_to_follow() const
        {
            return this->Horse_to_follow;
        }

        bool horse::set_Horse_to_follow(horse* horse)
        {
            if(horse == this)//trying to follow himself
            {
                return false;
            }
            if(horse == this->Horse_to_follow)
            {
                return true ;
            }
            this->Horse_to_follow = horse;
            return true;
        }

        void horse::set_horse_herd(herd* herd)
        {
            this->horse_herd = herd;
        } 
        void horse::set_visited(bool value) {
            this->visited = value ; 
        }
        int horse::get_version() const {
            return this->version;
        } 
        void horse::set_version(int amount )
        {
            this->version = amount;
        }
        bool horse::get_is_follow_here() const
        {
            return this->is_follow_here;
        } 
        void horse::set_is_follow_here(bool val)
        {
            this->is_follow_here = val;
        } 

     int herdIdKeyFn(const herd& herd) {
            return herd.get_herdId();
        } 
        int horseIdKeyFn(const horse& h){
            return h.get_HorseId();
        }