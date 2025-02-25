// Copyright 2022-2023 The Jule Programming Language.
// Use of this source code is governed by a BSD 3-Clause
// license that can be found in the LICENSE file.

#ifndef __JULE_UTF8_HPP
#define __JULE_UTF8_HPP

//
// Implements functions and constants to support text encoded in
// UTF-8 for Jule strings. It includes functions to translate between
// runes and UTF-8 byte sequences.
// See https://en.wikipedia.org/wiki/UTF-8
//
// Based on std::unicode::utf8
//

#include <tuple>

#include "types.hpp"
#include "slice.hpp"

namespace jule {

    constexpr signed int UTF8_RUNE_ERROR{ 65533 };
    constexpr signed int UTF8_MASKX{ 63 };
    constexpr signed int UTF8_MASK2{ 31 };
    constexpr signed int UTF8_MASK3{ 15 };
    constexpr signed int UTF8_MASK4{ 7 };
    constexpr signed int UTF8_LOCB{ 128 };
    constexpr signed int UTF8_HICB{ 191 };
    constexpr signed int UTF8_XX{ 241 };
    constexpr signed int UTF8_AS{ 240 };
    constexpr signed int UTF8_S1{ 2 };
    constexpr signed int UTF8_S2{ 19 };
    constexpr signed int UTF8_S3{ 3 };
    constexpr signed int UTF8_S4{ 35 };
    constexpr signed int UTF8_S5{ 52 };
    constexpr signed int UTF8_S6{ 4 };
    constexpr signed int UTF8_S7{ 68 };
    constexpr signed int UTF8_RUNE1_MAX{ 127 };
    constexpr signed int UTF8_RUNE2_MAX{ 2047 };
    constexpr signed int UTF8_RUNE3_MAX{ 65535 };
    constexpr signed int UTF8_TX{ 128 };
    constexpr signed int UTF8_T2{ 192 };
    constexpr signed int UTF8_T3{ 224 };
    constexpr signed int UTF8_T4{ 240 };
    constexpr signed int UTF8_MAX_RUNE{ 1114111 };
    constexpr signed int UTF8_SURROGATE_MIN{ 55296 };
    constexpr signed int UTF8_SURROGATE_MAX{ 57343 };

    // Declarations

    struct UTF8AcceptRange;
    std::tuple<jule::I32, jule::Int> utf8_decode_rune_str(const char *s, const jule::Int &len);
    jule::Slice<jule::U8> utf8_rune_to_bytes(const jule::I32 &r);

    // Definitions

    constexpr jule::U8 utf8_first[256] = {
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS, jule::UTF8_AS,
        jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX,
        jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX,
        jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX,
        jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX,
        jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1,
        jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1, jule::UTF8_S1,
        jule::UTF8_S2, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S3, jule::UTF8_S4, jule::UTF8_S3, jule::UTF8_S3,
        jule::UTF8_S5, jule::UTF8_S6, jule::UTF8_S6, jule::UTF8_S6, jule::UTF8_S7, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX, jule::UTF8_XX,
    };

    struct UTF8AcceptRange{ const jule::U8 lo, hi; };

    constexpr struct jule::UTF8AcceptRange utf8_accept_ranges[16] = {
        { jule::UTF8_LOCB, jule::UTF8_HICB },
        { 0xA0, jule::UTF8_HICB },
        { jule::UTF8_LOCB, 0x9F },
        { 0x90, jule::UTF8_HICB },
        { jule::UTF8_LOCB, 0x8F },
    };

    std::tuple<jule::I32, jule::Int>
    utf8_decode_rune_str(const char *s, const jule::Int &len) {
        if (len < 1)
            return std::make_tuple<jule::I32, jule::Int>(jule::UTF8_RUNE_ERROR, 0);

        const jule::U8 s0{ static_cast<jule::U8>(s[0]) };
        const jule::U8 x{ jule::utf8_first[s0] };
        if (x >= jule::UTF8_AS) {
            const jule::I32 mask{ x << 31 >> 31 };
            return std::make_tuple( (static_cast<jule::I32>(s[0])&~mask) |
                                    (jule::UTF8_RUNE_ERROR&mask), 1);
        }

        const jule::Int sz{ static_cast<jule::Int>(x&7) };
        const struct jule::UTF8AcceptRange accept{ jule::utf8_accept_ranges[x>>4] };
        if (len < sz)
            return std::make_tuple<jule::I32, jule::Int>( jule::UTF8_RUNE_ERROR, 1 );

        const jule::U8 s1{ static_cast<jule::U8>(s[1]) };
        if (s1 < accept.lo || accept.hi < s1)
            return std::make_tuple<jule::I32, jule::Int>(jule::UTF8_RUNE_ERROR, 1);

        if (sz <= 2)
            return std::make_tuple<jule::I32, jule::Int>(
                (static_cast<jule::I32>(s0&jule::UTF8_MASK2)<<6) |
                 static_cast<jule::I32>(s1&jule::UTF8_MASKX), 2);

        const jule::U8 s2{ static_cast<jule::U8>(s[2]) };
        if (s2 < jule::UTF8_LOCB || jule::UTF8_HICB < s2)
            return std::make_tuple<jule::I32, jule::Int>(jule::UTF8_RUNE_ERROR, 1);

        if (sz <= 3)
            return std::make_tuple<jule::I32, jule::Int>(
                (static_cast<jule::I32>(s0&jule::UTF8_MASK3)<<12) |
                (static_cast<jule::I32>(s1&jule::UTF8_MASKX)<<6) |
                 static_cast<jule::I32>(s2&jule::UTF8_MASKX), 3);

        const jule::U8 s3{ static_cast<jule::U8>(s[3]) };
        if (s3 < jule::UTF8_LOCB || jule::UTF8_HICB < s3)
            return std::make_tuple<jule::I32, jule::Int>(jule::UTF8_RUNE_ERROR, 1);

        return std::make_tuple((static_cast<jule::I32>(s0&jule::UTF8_MASK4)<<18) |
                               (static_cast<jule::I32>(s1&jule::UTF8_MASKX)<<12) |
                               (static_cast<jule::I32>(s2&jule::UTF8_MASKX)<<6) |
                                static_cast<jule::I32>(s3&jule::UTF8_MASKX), 4);
    }

    jule::Slice<jule::U8> utf8_rune_to_bytes(const jule::I32 &r) {
        if (static_cast<jule::U32>(r) <= jule::UTF8_RUNE1_MAX)
            return jule::Slice<jule::U8>({static_cast<jule::U8>(r)});

        const jule::U32 i{ static_cast<jule::U32>(r) };
        if (i < jule::UTF8_RUNE2_MAX) {
            return jule::Slice<jule::U8>({ static_cast<jule::U8>(jule::UTF8_T2|static_cast<jule::U8>(r>>6)),
                                           static_cast<jule::U8>(jule::UTF8_TX|(static_cast<jule::U8>(r)&jule::UTF8_MASKX)) });
        }

        jule::I32 _r{ r };
        if (i > jule::UTF8_MAX_RUNE ||
            (jule::UTF8_SURROGATE_MIN <= i && i <= jule::UTF8_SURROGATE_MAX))
            _r = jule::UTF8_RUNE_ERROR;

        if (i <= jule::UTF8_RUNE3_MAX)
            return jule::Slice<jule::U8>({ static_cast<jule::U8>(jule::UTF8_T3|static_cast<jule::U8>(_r>>12)),
                                           static_cast<jule::U8>(jule::UTF8_TX|(static_cast<jule::U8>(_r>>6)&jule::UTF8_MASKX)),
                                           static_cast<jule::U8>(jule::UTF8_TX|(static_cast<jule::U8>(_r)&jule::UTF8_MASKX)) });

        return jule::Slice<jule::U8>({ static_cast<jule::U8>(jule::UTF8_T4|static_cast<jule::U8>(_r>>18)),
                                       static_cast<jule::U8>(jule::UTF8_TX|(static_cast<jule::U8>(_r>>12)&jule::UTF8_MASKX)),
                                       static_cast<jule::U8>(jule::UTF8_TX|(static_cast<jule::U8>(_r>>6)&jule::UTF8_MASKX)),
                                       static_cast<jule::U8>(jule::UTF8_TX|(static_cast<jule::U8>(_r)&jule::UTF8_MASKX)) });
    }

} // namespace jule

#endif // #ifndef __JULE_UTF8_HPP
