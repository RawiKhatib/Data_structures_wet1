
#include <iostream>
#include "exceptions.h"
#include "values.h"


        herd::herd(int herdId) : herdId(herdId) , num_of_horses(0) , first_horse(nullptr) , circle_herd(false) 
        {
            if(herdId <= 0)
            {
               throw Invalid_Input();
            }
        }

        bool herd::get_circle_horse() const
        {
            return this->circle_herd;
        }
        void herd::set_circle_horse(bool newResult)
        {
            this->circle_herd = newResult;
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

        horse* herd::get_first_horse() const
        {
            return this->first_horse; 
        }
        void herd::set_first_horse(horse *horse)
        {
            first_horse = horse ; 
        }

        herd& herd::operator=(const herd& other)
        {
            if (this == &other) {
                return *this; // Self-assignment check
            }
            num_of_horses = other.num_of_horses;
            delete first_horse; 
            if (other.first_horse) {
                first_horse = new horse(*other.first_horse); 
            } else {
                first_horse = nullptr;
            }

            return *this;
        }


        horse::horse(const int horseId, const int speed)
        : horseId(horseId), speed(speed), Horse_to_follow(nullptr), prev_horse(nullptr) , horse_herd(nullptr)
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

        horse* horse::get_prev_Horse() const
        {
            return this->prev_horse;
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
        bool horse::set_prev_horse(horse* horse)
        {
            if(this->prev_horse == horse)
            {
                return true;
            }
            if(horse == this)
            {
                return false;
            }
            this->prev_horse = horse;
            return true;
        }
        void horse::set_horse_herd(herd* herd)
        {
            this->horse_herd = herd;
        }

     int herdIdKeyFn(const herd& herd) {
            return herd.get_herdId();
        } 
        int horseIdKeyFn(const horse& h){
            return h.get_HorseId();
        }