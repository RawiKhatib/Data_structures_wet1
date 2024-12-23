// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"
#include "wet1util.h"


#define FIRST_HORSE 1


Plains::Plains()
    : horse_Tree(horseIdKeyFn),         // Initialize horse_Tree with horseIdKeyFn
      herds_Tree(herdIdKeyFn),          // Initialize herds_Tree with herdIdKeyFn
      empty_herds_Tree(herdIdKeyFn)     // Initialize empty_herds_Tree with herdIdKeyFn
{}


Plains::~Plains(){}
   


StatusType Plains::add_herd(int herdId)
{
    try {
        //Node<herd> *newHerd = new Node<herd>(herdId);
        herd newHerd = herd(herdId);

        bool inserted = empty_herds_Tree.insert(newHerd);
        Node<herd> *find = herds_Tree.find(herdId) ; 
        //if inserted is false this means the herd is already in the tree
        
        if (!inserted || find != nullptr) {
            return StatusType::FAILURE;
        }
    } 
    catch (const std::bad_alloc&) {
    // Handle failed memory allocation
        return StatusType::ALLOCATION_ERROR; // Return invalid input if allocation fails
    } 
    catch (const Invalid_Input& e) {
        return StatusType::INVALID_INPUT;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::remove_herd(int herdId)
{
    if(herdId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    bool remove = empty_herds_Tree.deleteValue(herdId); 
    if(!remove) 
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::add_horse(int horseId, int speed)
{
    try {
        horse newHorse = horse(horseId,speed);
    
        bool inserted = horse_Tree.insert(newHorse); 
        //if inserted is false this means the horse is already in the tree
        
        if (!inserted){
            return StatusType::FAILURE;
        }
    } 
    catch (const std::bad_alloc&) {
    // Handle failed memory allocation
        return StatusType::ALLOCATION_ERROR; // Return invalid input if allocation fails
    } 
    catch (const Invalid_Input& e) {
        return StatusType::INVALID_INPUT;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::join_herd(int horseId, int herdId)
{   
    if(horseId <= 0 || herdId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    //1)check if the herd is empty or does not  exists or horse is not found
    Node<herd> *find_herd = herds_Tree.find(herdId) ;
    Node<herd> *find_empty_herd = empty_herds_Tree.find(herdId) ;
    Node<horse> *find_horse = horse_Tree.find(horseId);

    if((find_empty_herd == nullptr && find_herd == nullptr ) || find_horse == nullptr)
    {
        return StatusType::FAILURE;
    }

    //check if the herd is not empty , update the horse and update the herd
    if(find_herd)
    {
        find_horse->getValue().set_Horse_to_follow(nullptr);
        find_horse->getValue().set_horse_herd(&find_herd->getValue());

        int newAmount = find_herd->getValue().get_num_of_horses() + 1;
        find_herd->getValue().set_num_of_horses(newAmount);
        bool inserted = find_herd->getValue().get_herd_horse_tree().insert(find_horse->getValue());
        if(inserted)
        {
            return  StatusType::SUCCESS ; 
        }
        else{
            return StatusType::FAILURE;
        }
        
    }

    //check if the herd is empty delete it , update the herd tree and the horse  
    else
    {
        empty_herds_Tree.deleteValue(herdId);

        herd NewHerd = herd(herdId);
        NewHerd.set_num_of_horses(FIRST_HORSE);
      try{
        herds_Tree.insert(NewHerd);
      } 
      catch (const std::bad_alloc&) {
    // Handle failed memory allocation
        return StatusType::ALLOCATION_ERROR; // Return invalid input if allocation fails
    } 
     catch (const Invalid_Input& e) {
        return StatusType::INVALID_INPUT;
    } 
        Node<herd> *find_herd_again = herds_Tree.find(herdId) ;

        bool inserted = find_herd_again->getValue().get_herd_horse_tree().insert(find_horse->getValue());
        if(inserted)
        {
            return StatusType::SUCCESS ;
        }
        else{
            return StatusType::FAILURE;
        } 
        
    }
}

StatusType Plains::follow(int horseId, int horseToFollowId)
{    
    if(horseId <= 0 || horseToFollowId <= 0 || horseToFollowId == horseId)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<horse> *find_horseId = horse_Tree.find(horseId);
    Node<horse> *find_horseFollowId = horse_Tree.find(horseToFollowId);

    bool same_herd = (find_horseFollowId->getValue().get_horse_herd()==
    find_horseId->getValue().get_horse_herd()) ? true : false;

    if(!find_horseId || !find_horseFollowId || !same_herd)
    {
        return StatusType::FAILURE;
    }

    
    bool set_result1 = find_horseId->getValue().set_Horse_to_follow(&find_horseFollowId->getValue());
    find_horseId->getValue().set_is_follow_here(true) ; 
    find_horseFollowId->getValue().set_is_follow_here(true) ; 
    if(!set_result1)
    {
        return StatusType::FAILURE;
    }
 
    return StatusType::SUCCESS;
    //in case he follows first horse : 
}

StatusType Plains::leave_herd(int horseId)
{
    if(horseId <= 0) 
    {
        return StatusType::INVALID_INPUT;
    }
    Node<horse> *find_horseId = horse_Tree.find(horseId);


    herd* horse_herd = find_horseId->getValue().get_horse_herd();
     if(find_horseId == nullptr || horse_herd == nullptr){
        return StatusType::FAILURE ; 
     }
     // update prev of the horseId check if prev is null and update the next of the prev 
     // update  horseId next 
     // update horse__herd , check num_of_horses and deal with it 
    find_horseId->getValue().set_horse_herd(nullptr);
    find_horseId->getValue().set_Horse_to_follow(nullptr);
     int new_num_of_horses = horse_herd->get_num_of_horses() ;
     new_num_of_horses = new_num_of_horses - 1 ; 
     horse_herd->set_num_of_horses(new_num_of_horses) ; 
     find_horseId->getValue().set_is_follow_here(false) ;

    if(new_num_of_horses == 0 ){
        remove_herd(horse_herd->get_herdId()) ;
        add_herd(horse_herd->get_herdId()) ; 
    }

    return StatusType::SUCCESS ;   
      


}

output_t<int> Plains::get_speed(int horseId)
{    
    // Validate the horseId
    if (horseId <= 0) {
        // Return with the INVALID_INPUT status
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    // Try to find the horse in the tree
    Node<horse>* find_horseId = horse_Tree.find(horseId);
    if (find_horseId == nullptr) {
        // Return with the FAILURE status if the horseId was not found
        return output_t<int>(StatusType::FAILURE);
    }

    // Retrieve the speed from the horse object
    int speed = find_horseId->getValue().get_speed();

    // Return the speed with the SUCCESS status
    return output_t<int>(speed);
      
}

output_t<bool> Plains::leads(int horseId, int otherHorseId)//fix this
{
    if (horseId <= 0 || otherHorseId <= 0 || horseId == otherHorseId)
    {
        return output_t<bool>(StatusType::INVALID_INPUT);
    }

    // Find the nodes for both horses
    Node<horse>* find_horseId = horse_Tree.find(horseId);
    Node<horse>* find_OtherHorseId = horse_Tree.find(otherHorseId);

    if (!find_horseId || !find_OtherHorseId)
    {
        return output_t<bool>(StatusType::FAILURE);
    }

    // Start traversing from find_horseId
    horse* temp = &find_horseId->getValue();

    while (temp)
    {
        temp = temp->get_Horse_to_follow();
        if (temp == &find_OtherHorseId->getValue())
        {
            // horseId leads to otherHorseId
            return output_t<bool>(true);
        }
        if (temp == &find_horseId->getValue())
        {
            // Avoid infinite loops in case of circular reference
            break;
        }
    }

    // horseId does not lead to otherHorseId
    return output_t<bool>(false);
}

void inorderTraversal(Node<shared_ptr<horse>> *node, bool &circle, int &leader, int current_version) {
        if ( circle || leader > 1 || node->getValue()->get_visited() == true || node == nullptr) {
            return ;
        }

        // Traverse the left subtree
        inorderTraversal(node->getLeft(), circle, leader, current_version);

        // Process the current node
        shared_ptr<horse> horse_ptr = node->getValue();

        horse_ptr->set_visited(true);
        current_version++;

        while(horse_ptr->get_Horse_to_follow()!= nullptr && horse_ptr->get_Horse_to_follow()->get_version() == horse_ptr->get_version() && horse_ptr->get_Horse_to_follow()->get_version() == current_version  ){
            if(horse_ptr->get_Horse_to_follow()->get_visited() == true ){
                circle = true ;
                break ;
            }
            horse_ptr->set_version(current_version) ;
            horse_ptr->get_Horse_to_follow()->set_visited(true) ;
            horse_ptr = horse_ptr->get_Horse_to_follow() ;
        }
        //check if we exit the while bc the next is null
        if(horse_ptr->get_Horse_to_follow() == nullptr){
            leader++ ;
            horse_ptr->set_version(current_version) ;

        }
        // or the other thing
        if(horse_ptr->get_Horse_to_follow()->get_version() != horse_ptr->get_version() ){
            horse_ptr->set_version(current_version) ;
        }

        // Traverse the right subtree
        inorderTraversal(node->getRight(), circle, leader, current_version);
    }

void after_inorderTraversal(Node<shared_ptr<horse>> *node){
    if (node == nullptr) {
        return;
    }

    // Traverse the left subtree
    after_inorderTraversal(node->getLeft());

    //check visited
    if(node->getValue()->get_visited()){
       node->getValue()->set_visited(false) ;
    }

    // Traverse the right subtree
    after_inorderTraversal(node->getRight());
}

output_t<bool> Plains::can_run_together(int herdId)
{
    if (herdId <= 0)
    {
        return output_t<bool>(StatusType::INVALID_INPUT);
    }

    Node<herd> *find_herd = herds_Tree.find(herdId);
    if (!find_herd)
    {
        return output_t<bool>(StatusType::FAILURE);
    }

    AVLTree<horse, int>  herds_horse_tree = find_herd->getValue().get_herd_horse_tree();
    bool circle = false ;
    int leader = 0 ;
    inorderTraversal(herds_horse_tree.getRoot(),circle , leader, 0 ) ;
     after_inorderTraversal(herds_horse_tree.getRoot()) ;
    if( circle || leader > 1 ){
    return  output_t<bool>(false);

    }
    return  output_t<bool>(true);

}