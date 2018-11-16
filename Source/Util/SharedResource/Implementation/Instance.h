#pragma once
#include "JuceHeader.h"
#include "SharedResource/Implementation/Implementation.h"
#include "SharedResource/SharedResource.h"

/**
 * @file  SharedResource/Implementation/Instance.h
 *
 * @brief  Manages the lifespan of a resource object by tracking each reference
 *         object tied to the resource.
 */
class SharedResource::Instance
{
private:
    /**
     * @brief  Creates the unique resource object instance.
     *
     * @param resourceKey  The resource's unique key identifier.
     */
    Instance(const juce::Identifier& resourceKey);

public:
    /* References need to add themselves to the handlers list on
       construction, and remove themselves on destruction. */
    friend class Reference;

    /* Instance may only be created as the parent class of Resource objects. */
    friend class Resource;

    /**
     * @brief  Destroys the resource instance once all of its references 
     *         have been destroyed.
     */
    virtual ~Instance();

    /**
     * @brief  Gets the unique key used to identify this resource Instance.
     *
     * @return  The resource's unique key identifier.
     */
    const juce::Identifier& getResourceKey() const;

private:
    /**
     * @brief  Runs an arbitrary function on each Reference object 
     *         connected to the resource.  This locks the resource for
     *         reading, so the function should not take any actions
     *         that would lock the resource for writing.
     *
     * @param handlerAction  Some action that should run for every reference
     *                       connected to this resource instance, passing in
     *                       a pointer to the Reference as a parameter.
     */
    void foreachReference
    (std::function<void(Reference*)> referenceAction);

    /* The resource's unique key identifier. */
    const juce::Identifier& resourceKey;

    /* Tracks all reference object associated with the resource. */
    juce::Array<Reference*> references;
};
