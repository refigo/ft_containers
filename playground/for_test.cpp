
template <class _Vec>
void mgo_print_vec(_Vec _vec) {
    for (typename _Vec::iterator it = _vec.begin()
        ; it != _vec.end()
        ; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}


    std::cout << "std" << '\n';
    mgo_print_vec(v);



    std::cout << "ft" << '\n';
    mgo_print_vec(v);

    
