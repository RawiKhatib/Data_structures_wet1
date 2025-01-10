
#include <iostream>
#include "exceptions.h"
#include "values.h"

        int herdIdKeyFn(const shared_ptr<herd> &herd) {
            return herd->get_herdId();
        }

        int horseIdKeyFn(const shared_ptr<horse> &h) {
            return h->get_HorseId();
        }

        herd::herd(int herdId) : herdId(herdId) , num_of_horses(0) ,  
         herd_horses_tree(make_shared<AVLTree<shared_ptr<horse>, int>>(horseIdKeyFn)) 
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

        shared_ptr<AVLTree<shared_ptr<horse>, int>> herd::get_herd_horse_tree() {
            return this->herd_horses_tree ;
        }

        horse::horse(const int horseId, const int speed)
        : horseId(horseId), speed(speed), Horse_to_follow(), horse_herd() , visited(false)
        ,version(0) , is_follow_here(0) , insert_version(0) , is_prev(false) 
        {
        if (horseId <= 0 || speed <= 0)
        {
            throw Invalid_Input();
        }
        }
        herd& herd::operator=(const herd& other) {
                    if (this == &other) {
                        return *this; // Handle self-assignment
                    }

                    // Copy members from `other` to `this`
                    this->num_of_horses = other.num_of_horses;
                    this->herd_horses_tree = other.herd_horses_tree; // Ensure `AVLTree` supports copying

                    // Note: `herdId` is `const` and cannot be reassigned
                    return *this;
        }

        const int horse::get_HorseId() const
        {
            return this->horseId;
        }

        const int horse::get_speed() const
        {
            return this->speed;
        }

        weak_ptr<herd> horse::get_horse_herd() const
        {
            return this->horse_herd;
        }

        weak_ptr<horse> horse::get_Horse_to_follow() {
            auto followPtr = Horse_to_follow.lock();
            if (!followPtr || followPtr->get_insert_version() != is_follow_here 
            || horse_herd.lock() != followPtr->get_horse_herd().lock()) {
                Horse_to_follow.reset();
                return weak_ptr<horse>();
            }
            return Horse_to_follow;
        }

        bool horse::set_Horse_to_follow(shared_ptr<horse> horse) {
            if (!horse|| horse.get() == this) {
                return false; // Cannot follow itself
            }
            Horse_to_follow = horse;
            return true;
        }
        void horse::set_horse_herd(shared_ptr<herd> herd)
        {
            this->horse_herd = herd;
        }

         bool horse::get_visited() const{
           return this->visited;
         }
        void horse::set_visited(bool value) {
            this->visited = value ;
        }
        int horse::get_version()  {
            return this->version;
        }
        void horse::set_version(int amount )
        {
            this->version = amount;
        }
        int horse::get_is_follow_here()
        {
            return this->is_follow_here;
        }
        void horse::set_is_follow_here(int val)
        {   
            this->is_follow_here = val;
        }

        int horse::get_insert_version() const
        {
            return this->insert_version;
        }
        void horse::set_insert_version(int amount)
        {    
            this->insert_version = amount;
        }

