#ifndef NODEPP_ERROR
#define NODEPP_ERROR

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class except_t { 
protected: string_t message; ulong ev;
public:

    template< class T, class = typename type::enable_if<type::is_class<T>::value,T>::type >
    except_t( const T& except_type ) noexcept : message( except_type.what() ) {}

    /*─······································································─*/

    except_t( const string_t& msg ) noexcept : message(msg) {}

    /*─······································································─*/

    except_t() noexcept : message("Something Went Wrong") {}

    /*─······································································─*/

    except_t( const char* msg ) noexcept : message(msg) {}

    /*─······································································─*/

    const char* what() const noexcept { return message.c_str(); }

    operator char*() const noexcept { return (char*)what(); }

    void print() const noexcept { console::error(message); } 
    
};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif