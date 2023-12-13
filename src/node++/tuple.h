#ifndef NODEPP_TUPLE
#define NODEPP_TUPLE

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp {

/*────────────────────────────────────────────────────────────────────────────*/

template <typename... Types> class tuple_t {};

template <typename Head, typename... Tail>
class tuple_t<Head, Tail...> : public tuple_t<Tail...> {
public: tuple_t() noexcept {}
    tuple_t( Head head, Tail... tail ) : tuple_t<Tail...>(tail...), head_(new Head(head)) {}
    tuple_t<Tail...> tail() const { return *this; }
    Head& head() const { return *head_; }
private:
    ptr_t<Head> head_;
};

/*────────────────────────────────────────────────────────────────────────────*/

namespace tuple {

    template <ulong Index, typename Head, typename... Tail >
    struct tuple_element { using type = typename tuple_element< Index - 1 , Tail...>::type; };

    template <typename Head, typename... Tail>
    struct tuple_element<0, Head, Tail...> { using type = Head; };

    /*─······································································─*/

    template <ulong Index, typename Head, typename... Tail>
    struct get_helper {
        static typename tuple_element<Index, Head, Tail...>::type& get(const tuple_t<Head, Tail...>& tuple) {
            return get_helper<Index - 1, Tail...>::get(tuple.tail());
        }
    };

    template <typename Head, typename... Tail>
    struct get_helper<0, Head, Tail...> {
        static Head& get(const tuple_t<Head, Tail...>& tuple) {
            return tuple.head();
        }
    };

    /*─······································································─*/

    template <ulong Index, typename... Types>
    typename tuple_element<Index, Types...>::type& get(const tuple_t<Types...>& tuple) {
        static_assert( Index < sizeof...(Types), "Index out of bounds in tuple get" );
        return get_helper<Index, Types...>::get(tuple);
    }

}

/*────────────────────────────────────────────────────────────────────────────*/

}

#endif