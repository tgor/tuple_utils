#ifndef TUTILS_STATIC_HPP
#define TUTILS_STATIC_HPP

/**
 * @file
 * @author
 * @version
*/

//! Utilities for tuples manipulation
namespace tuple_utils
{

///@internal

/**
 *@brief Helper class which, when derived from, prevents deriving class from being instantiated
 */
struct static_
{
    private:
    static_() = delete;
    static_(const static_&) = delete;
    static_& operator=(const static_&) = delete;
};

///@endinternal
} // namespace tuple_utils

#endif // TUTILS_STATIC_HPP
