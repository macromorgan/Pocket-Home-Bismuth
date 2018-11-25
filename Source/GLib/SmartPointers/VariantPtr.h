#pragma once
#include <gio/gio.h>
#include "GLib/SmartPointers/ScopedGPointer.h"

/**
 * @file  GLib/SmartPointers/VariantPtr.h
 *
 * @brief  Defines a ScopedGPointer that holds a GVariant*. 
 */
namespace GLib
{
    /**
     * @brief  Provides the unreferencing function used for GVariant* data.
     */
    struct VariantUnref
    {
        /**
         * @brief  Unreferences GVariant data.
         *
         * @param context  A non-null variant pointer to unreference.
         */
        static void unref(GVariant* variant)
        {
            g_variant_unref(variant);
        }
    };

    /**
     * @brief  Stores and automatically unreferences a GVariant*.
     */
    typedef ScopedGPointer<GVariant*, VariantUnref> VariantPtr;
}
