/**
* Flow Libs - Math
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_MATH_RANGE3T_H
#define _FLOWLIBS_MATH_RANGE3T_H

#include "library.h"

#include "Vector3T.h"

#include "../core/json.h"

#include <string>
#include <limits>


namespace flow
{
    template <typename T>
    class Range3T
    {
        //  Constructors and destructor ----------------------------------

    public:
        Range3T() { }
        Range3T(const Vector3T<T>& lowerBound, const Vector3T<T>& upperBound)
            : m_lowerBound(lowerBound), m_upperBound(upperBound) { }
        Range3T(T xMin, T yMin, T zMin, T xMax, T yMax, T zMax)
            : m_lowerBound(xMin, yMin, zMin), m_upperBound(xMax, yMax, zMax) { }

        //  Public commands ----------------------------------------------

    public:
        void set(const Vector3T<T>& lowerBound, const Vector3T<T>& upperBound);
        void set(T xMin, T yMin, T zMin, T xMax, T yMax, T zMax);
        void setZero();

        void setLowerBound(const Vector3T<T>& lowerBound);
        void setLowerBound(T xMin, T yMin, T zMin);
        void setUpperBound(const Vector3T<T>& upperBound);
        void setUpperBound(T xMax, T yMax, T zMax);

        /// Invalidates the range by setting the lower bound to the maximum value
        /// and the upper bound to the minimum value.
        void invalidate();

        /// Moves the upper and lower bound by the given offset.
        void move(const Vector3T<T>& offset);

        /// Includes the given point. The range is extended such that
        /// the given point lies inside.
        void include(const Vector3T<T>& point);

        /// Unites this with the given range. The result is a range that
        /// covers both input ranges.
        void uniteWith(const Range3T<T>& other);

        /// Intersects this with the given range. The range is set to
        /// zero if there is no overlap between the ranges.
        void intersectWith(const Range3T<T>& other);

        /// Normalizes the range, i.e. for each component swaps the lower and upper bound
        /// if the lower bound is greater than the upper bound.
        void normalize();

        //  Public queries -----------------------------------------------

        const Vector3T<T>& lowerBound() const { return m_lowerBound; }
        const Vector3T<T>& upperBound() const { return m_upperBound; }

        /// Returns the center of the range, which is the center point
        /// of the range for each dimension.
        const Vector3T<T> center() const;

        /// Returns the distance between lower and upper bound. The result can
        /// be negative if the range is not normal, i.e. upper bound is smaller
        /// than lower bound.
        const Vector3T<T> size() const;

        /// Interprets the range as a 3D box and returns its volume.
        const T volume() const;

        /// Returns the difference between upper and lower bound of the x component.
        const T sizeX() const { return m_upperBound.x - m_lowerBound.x; }
        
        /// Returns the difference between upper and lower bound of the y component.
        const T sizeY() const { return m_upperBound.y - m_lowerBound.y; }

        /// Returns the difference between upper and lower bound of the z component.
        const T sizeZ() const { return m_upperBound.z - m_lowerBound.z; }

        /// A range is valid if for each component the upper bound is greater
        /// or equal to the lower bound.
        bool isValid() const;
        /// A range is empty if the upper bound is equal to the lower bound.
        bool isEmpty() const;
        /// Same as isEmpty().
        bool isNull() const { return isEmpty(); }

        /// Returns true if the given range is fully included in this one.
        bool includes(const Range3T<T>& range) const;

        /// Returns true if the given point is included in the range.
        bool includes(const Vector3T<T>& point) const;

        /// Returns true if this and the given range overlap. Also returns
        /// true if the overlap consists of a single point, e.g. if
        /// this range's upper bound equals other range's lower bound.
        bool intersects(const Range3T<T>& range) const;

        //  Internal data members ----------------------------------------

    private:
        Vector3T<T> m_lowerBound;
        Vector3T<T> m_upperBound;
    };

    // Members ---------------------------------------------------------------------

    template <typename T>
    inline void Range3T<T>::set(const Vector3T<T>& lowerBound, const Vector3T<T>& upperBound)
    {
        m_lowerBound = lowerBound;
        m_upperBound = upperBound;
    }

    template <typename T>
    inline void Range3T<T>::set(T xMin, T yMin, T zMin, T xMax, T yMax, T zMax)
    {
        m_lowerBound.set(xMin, yMin, zMin);
        m_upperBound.set(xMax, yMax, zMax);
    }

    template <typename T>
    inline void Range3T<T>::setZero()
    {
        m_lowerBound.setZero();
        m_upperBound.setZero();
    }

    template <typename T>
    inline void Range3T<T>::setLowerBound(const Vector3T<T>& lowerBound)
    {
        m_lowerBound = lowerBound;
    }

    template <typename T>
    inline void Range3T<T>::setLowerBound(T xMin, T yMin, T zMin)
    {
        m_lowerBound.set(xMin, yMin, zMin);
    }

    template <typename T>
    inline void Range3T<T>::setUpperBound(const Vector3T<T>& upperBound)
    {
        m_upperBound = upperBound;
    }

    template <typename T>
    inline void Range3T<T>::setUpperBound(T xMax, T yMax, T zMax)
    {
        m_upperBound.set(xMax, yMax, zMax);
    }

    template <typename T>
    inline void Range3T<T>::invalidate()
    {
        m_lowerBound.setAll(std::numeric_limits<T>::max());
        m_upperBound.setAll(std::numeric_limits<T>::lowest());
    }

    template <typename T>
    inline void Range3T<T>::move(const Vector3T<T>& offset)
    {
        m_lowerBound += offset;
        m_upperBound += offset;
    }

    template <typename T>
    inline void Range3T<T>::include(const Vector3T<T>& point)
    {
        m_lowerBound = min(m_lowerBound, point);
        m_upperBound = max(m_upperBound, point);
    }

    template <typename T>
    inline void Range3T<T>::uniteWith(const Range3T<T>& other)
    {
        m_lowerBound = min(m_lowerBound, other.m_lowerBound);
        m_upperBound = max(m_upperBound, other.m_upperBound);
    }

    template <typename T>
    inline void Range3T<T>::intersectWith(const Range3T<T>& other)
    {
        m_lowerBound = max(m_lowerBound, other.m_lowerBound);
        m_upperBound = min(m_upperBound, other.m_upperBound);

        if (m_lowerBound.x > m_upperBound.x) m_upperBound.x = m_lowerBound.x;
        if (m_lowerBound.y > m_upperBound.y) m_upperBound.y = m_lowerBound.y;
        if (m_lowerBound.z > m_upperBound.z) m_upperBound.z = m_lowerBound.z;
    }

    template <typename T>
    inline void Range3T<T>::normalize()
    {
        if (m_lowerBound.x > m_upperBound.x) std::swap(m_lowerBound.x, m_upperBound.x);
        if (m_lowerBound.y > m_upperBound.y) std::swap(m_lowerBound.y, m_upperBound.y);
        if (m_lowerBound.z > m_upperBound.z) std::swap(m_lowerBound.z, m_upperBound.z);
    }

    template <typename T>
    inline const Vector3T<T> Range3T<T>::center() const
    {
        return (m_upperBound + m_lowerBound) * T(0.5);
    }


    template <typename T>
    inline const Vector3T<T> Range3T<T>::size() const
    {
        return m_upperBound - m_lowerBound;
    }

    template <typename T>
    inline const T Range3T<T>::volume() const
    {
        Vector3T<T> size = m_upperBound - m_lowerBound;
        return size.x * size.y * size.z;
    }

    template <typename T>
    inline bool Range3T<T>::isValid() const
    {
        return m_lowerBound.x <= m_upperBound.x
            && m_lowerBound.y <= m_upperBound.y
            && m_lowerBound.z <= m_upperBound.z;
    }

    template <typename T>
    inline bool Range3T<T>::isEmpty() const
    {
        Vector3T<T> size = m_upperBound - m_lowerBound;
        return (size.x * size.y * size.z) == 0;
    }

    template <typename T>
    inline bool Range3T<T>::includes(const Range3T<T>& other) const
    {
        return m_lowerBound.x <= other.m_lowerBound.x
            && m_lowerBound.y <= other.m_lowerBound.y
            && m_lowerBound.z <= other.m_lowerBound.z
            && m_upperBound.x >= other.m_upperBound.x
            && m_upperBound.y >= other.m_upperBound.y
            && m_upperBound.z >= other.m_upperBound.z;
    }

    template <typename T>
    inline bool Range3T<T>::includes(const Vector3T<T>& point) const
    {
        return m_lowerBound.x <= point.x
            && m_lowerBound.y <= point.y
            && m_lowerBound.z <= point.z
            && m_upperBound.x >= point.x
            && m_upperBound.y >= point.y
            && m_upperBound.z >= point.z;
    }

    template <typename T>
    inline bool Range3T<T>::intersects(const Range3T<T>& other) const
    {
        return (m_lowerBound.x <= other.m_upperBound.x
            && m_lowerBound.y <= other.m_upperBound.y
            && m_lowerBound.z <= other.m_upperBound.z)
            || (m_upperBound.x >= other.m_lowerBound.x
            && m_upperBound.y >= other.m_lowerBound.y
            && m_upperBound.z >= other.m_lowerBound.z);
    }

    /// Writes a text representation of the range to the given stream.
    template <typename REAL, typename C>
    std::basic_ostream<C, std::char_traits<C>>& operator<<(
        std::basic_ostream<C, std::char_traits<C>>& stream, const Range3T<REAL>& range)
    {
        stream << range.lowerBound() << " - " << range.upperBound();
        return stream;
    }

    // Typedefs --------------------------------------------------------------------

    /// 3-component range of type float
    typedef Range3T<float> Range3f;

    /// 3-component range of type double
    typedef Range3T<double> Range3d;

    /// 3-component range of type integer
    typedef Range3T<int> Range3i;
}


#endif // _FLOWLIBS_MATH_RANGE3T_H
