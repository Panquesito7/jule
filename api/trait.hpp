// Copyright 2022-2023 The Jule Programming Language.
// Use of this source code is governed by a BSD 3-Clause
// license that can be found in the LICENSE file.

#ifndef __JULE_TRAIT_HPP
#define __JULE_TRAIT_HPP

#include <typeinfo>
#include <ostream>
#include <cstring>

#include "types.hpp"
#include "panic.hpp"
#include "error.hpp"
#include "ref.hpp"

namespace jule {

    // Wrapper structure for traits.
    template<typename Mask>
    struct Trait;

    template<typename Mask>
    struct Trait {
    public:
        mutable jule::Ref<Mask> data{};
        const char *type_id { nullptr };

        Trait<Mask>(void) = default;
        Trait<Mask>(std::nullptr_t) {}

        template<typename T>
        Trait<Mask>(const T &data) {
            T *alloc{ new(std::nothrow) T };
            if (!alloc)
                jule::panic(jule::ERROR_MEMORY_ALLOCATION_FAILED);

            *alloc = data;
#ifdef __JULE_DISABLE__REFERENCE_COUNTING
            this->data = jule::Ref<Mask>::make(static_cast<Mask*>(alloc), nullptr);
#else
            this->data = jule::Ref<Mask>::make(static_cast<Mask*>(alloc));
#endif
            this->type_id = typeid(T).name();
        }

        template<typename T>
        Trait<Mask>(const jule::Ref<T> &ref) {
#ifdef __JULE_DISABLE__REFERENCE_COUNTING
            this->data = jule::Ref<Mask>::make(static_cast<Mask*>(ref.alloc), nullptr);
#else
            this->data = jule::Ref<Mask>::make(static_cast<Mask*>(ref.alloc), ref.ref);
            if (ref.real())
                this->data.add_ref();
#endif
            this->type_id = typeid(ref).name();
        }

        Trait<Mask>(const jule::Trait<Mask> &src)
        { this->operator=(src); }

        void dealloc(void)
        { this->data.drop(); }

        inline void must_ok(void) const {
            if (this->operator==(nullptr))
                jule::panic(jule::ERROR_INVALID_MEMORY);
        }

        template<typename T>
        inline jule::Bool type_is(void) const {
            if (this->operator==(nullptr))
                return false;

            return std::strcmp(this->type_id, typeid(T).name()) == 0;
        }

        inline Mask &get(void) {
#ifndef __JULE_DISABLE__SAFETY
            this->must_ok();
#endif
            return this->data;
        }

        inline Mask &get(void) const {
#ifndef __JULE_DISABLE__SAFETY
            this->must_ok();
#endif
            return this->data;
        }

        ~Trait(void) {}

        template<typename T>
        operator T(void) {
#ifndef __JULE_DISABLE__SAFETY
            this->must_ok();
            if (std::strcmp(this->type_id, typeid(T).name()) != 0)
                jule::panic(jule::ERROR_INCOMPATIBLE_TYPE);
#endif
            return *reinterpret_cast<T*>(this->data.alloc);
        }

        template<typename T>
        operator jule::Ref<T>(void) {
#ifndef __JULE_DISABLE__SAFETY
            this->must_ok();
            if (std::strcmp(this->type_id, typeid(jule::Ref<T>).name()) != 0)
                jule::panic(jule::ERROR_INCOMPATIBLE_TYPE);
#endif

#ifndef __JULE_DISABLE__REFERENCE_COUNTING
            this->data.add_ref();
#endif
            return jule::Ref<T>::make(
                reinterpret_cast<T*>(this->data.alloc), this->data.ref);
        }

        inline void operator=(const std::nullptr_t)
        { this->dealloc(); }

        inline void operator=(const jule::Trait<Mask> &src) {
            // Assignment to itself.
            if (this->data.alloc != nullptr && this->data.alloc == src.data.alloc)
                return;

            this->dealloc();
            if (src == nullptr)
                return;
            this->data = src.data;
            this->type_id = src.type_id;
        }

        inline jule::Bool operator==(const jule::Trait<Mask> &src) const
        { return this->data.alloc == this->data.alloc; }

        inline jule::Bool operator!=(const jule::Trait<Mask> &src) const
        { return !this->operator==(src); }

        inline jule::Bool operator==(std::nullptr_t) const
        { return this->data.alloc == nullptr; }

        inline jule::Bool operator!=(std::nullptr_t) const
        { return !this->operator==(nullptr); }

        friend inline std::ostream &operator<<(std::ostream &stream,
                                               const jule::Trait<Mask> &src)
        { return stream << src.data.alloc; }
    };

} // namespace jule

#endif // #ifndef __JULE_TRAIT_HPP
