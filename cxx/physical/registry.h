/** \file
 * A registry for physical::quantity types that have been initialized
 * properly.
 *
 * Copyright 2008 Spencer E. Olson
 *
 * */

#ifndef PHYSICAL_REGISTRY_H
#define PHYSICAL_REGISTRY_H

#include <string>
#include <map>

/** Just a useful set of tools to help with the registry problem. */
namespace monkeywrench {
    static std::vector<std::string> id_stack;

    int push_namespace(const std::string & id) {
        id_stack.push_back(id);
        return 0;
    }

    int pop_namespace() {
        id_stack.pop_back();
        return 0;
    }

    std::string get_namespace() {
        std::string retval;
        if (id_stack.size() > 0)
            retval = id_stack[0];
        for (unsigned int i = 1; i < id_stack.size(); i++) {
            retval.append("::").append(id_stack[i]);
        }
        return retval;
    }

    std::string get_prefix() {
        if (id_stack.size() > 0)
            return get_namespace() + "::";
        else
            return "";
    }
}



namespace physical {

    /* **** BEGIN PHYSICAL QUANTITY REGISTRY **** */
    namespace registry {

        template <class table>
        static typename table::const_iterator
        next_lower_bound(const table & tab, const std::string & txt) {
            std::string txtp1 = txt;
            txtp1[txt.length()-1] = ((char)*(txt.end()-1)) + (char)1;
            return tab.lower_bound(txtp1);
        }


        struct StringMatcher {
            StringMatcher(const std::string & expr) : expr(expr) {}
            bool matches(const std::string & test) {
                return (expr == test);
            }
            const std::string & expr;
        };

        template <class Matcher = StringMatcher >
        struct importer {
            importer() {}
            template <class table>
            void operator()(table & tab,
                            const std::string & base,
                            const std::string & regex,
                            const std::string & new_ns = "") {
                bool import_all = regex == "*";
                Matcher matcher(regex);

                if (base.length() <1)
                    /* Import doesn't mean much without a base that is to be
                     * removed. */
                    return;

                std::string to = (new_ns == "") ? "" : new_ns + "::";
                table scratch;
                typename table::const_iterator i = tab.lower_bound(base),
                                               f = next_lower_bound(tab, base);
                for (; i != f; i++) {
                    std::string newkey = i->first.substr(base.length());
                    if(newkey.length() < 1) continue;
                    if(newkey.length() > 2 && newkey.substr(0,2) == "::")
                        newkey = newkey.substr(2);

                    /* test the regex */
                    if (!import_all && !matcher.matches(newkey))
                        continue;

                    scratch[to + newkey] = i->second;
                }

                /* now copy the scratch space over into the real table. */
                tab.insert(scratch.begin(), scratch.end()); 
            }
        };

        template <class Container, class Iter>
        void erase_items(Container & c, Iter i, const Iter f) {
            for (; i!=f; c.erase(*i), i++);
        }
        
        
        template < class Matcher = StringMatcher >
        struct clearer {
            template <class table>
            void operator()(table & tab,
                            const std::string & base,
                            const std::string & regex) {
                if (regex == "") {
                    /* We've been given a single case to try and clear. */
                    typename table::iterator i = tab.find(base);
                    if (i != tab.end())
                        tab.erase(i);
                    return;
                }
    
                /* We've been given a possible pattern to match many symbols to
                 * clear. */
                bool clear_all = regex == "*";
                Matcher matcher(regex);
    
                std::vector<std::string> scratch;
    
                typename table::const_iterator i, f;
    
                if ( base.length() > 0) {
                    i = tab.lower_bound(base);
                    f = next_lower_bound(tab,base);
                } else {
                    i = tab.begin();
                    f = tab.end();
                }
    
                for (; i != f; i++) {
                    std::string newkey = i->first.substr(base.length());
                    if(newkey.length() < 1) continue;
                    if(newkey.length() > 2 && newkey.substr(0,2) == "::")
                        newkey = newkey.substr(2);
    
                    /* test the regex */
                    if (!clear_all && !matcher.matches(newkey))
                        continue;
    
                    scratch.push_back(i->first);
                }
    
                /* now delete each item listed in the scratch space */
                erase_items(tab, scratch.begin(), scratch.end());
            }
        };



        /** A physical::quantity<T> register singleton that allows an easy
         * generation of a list of quantities that have been created, provided, of
         * course, that the quantity_register<...>::record function is called
         * with the namespace/name of the quantity. */  
        template<class T>
        struct recorder {
            typedef std::map<std::string, T*> list_type;
            list_type list;

            recorder() : list() {}
            ~recorder() {}

            void record(const std::string & n, T * ref) {
                if (n == "") return;
                std::string fqn = monkeywrench::get_prefix() + n;
                typename list_type::value_type bob = std::make_pair(fqn, ref);
                list[fqn] = ref;
            }

            int import(const std::string & base,
                       const std::string & regex,
                       const std::string & new_ns = "") {
                registry::importer<>()(list, base, regex, new_ns);
                return 0;
            }


            static recorder & instance() {
                static recorder * rec = new recorder();
                return *rec;
            }
        };



        
    }
    /* ****   END PHYSICAL QUANTITY REGISTRY **** */

}
#endif // PHYSICAL_REGISTRY_H
