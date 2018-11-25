#include "GLib/SmartPointers/ObjectPtr.h"
#include "NMPPActiveConnection.h"

/* Rename smart pointers for brevity: */
typedef GLib::ObjectPtr<NMActiveConnection*> NMActiveConnectionPtr;
typedef GLib::ObjectPtr<NMObject*> NMObjectPtr;

/*
 * Creates a NMPPActiveConnection sharing a GObject with an existing
 * NMPPActiveConnection.
 */
NMPPActiveConnection::NMPPActiveConnection(const NMPPActiveConnection& toCopy) :
GLib::Object(toCopy, NM_TYPE_ACTIVE_CONNECTION) { }
 
/*
 * Creates a NMPPActiveConnection to contain a NMActiveConnection object.
 */
NMPPActiveConnection::NMPPActiveConnection(NMActiveConnection* toAssign) :
GLib::Object(G_OBJECT(toAssign), NM_TYPE_ACTIVE_CONNECTION) { }
    
/**
 * Creates a null NMPPActiveConnection.
 */
NMPPActiveConnection::NMPPActiveConnection() :
GLib::Object(NM_TYPE_ACTIVE_CONNECTION) { }

/*
 * Get the connection path stored by this object.
 */
const char* NMPPActiveConnection::getPath() const
{
    const char* path = "";
    NMObjectPtr connection(NM_OBJECT(getGObject()));
    if(connection != nullptr)
    {
        path = nm_object_get_path(connection);
        if(path == nullptr)
        {
            path = "";
        }
    }
    return path;
}
    
/*
 * Gets the path of the access point used to activate this connection.
 */
const char* NMPPActiveConnection::getAccessPointPath() const
{
    const char* path = "";
    NMActiveConnectionPtr connection(NM_ACTIVE_CONNECTION(getGObject()));
    if(connection != nullptr)
    {
        path = nm_active_connection_get_specific_object(connection);
        if(path == nullptr)
        {
            path = "";
        }
    }
    return path;
}

/*
 * Checks if an access point object is linked to this active connection.
 */
bool NMPPActiveConnection::isConnectedAccessPoint
(const NMPPAccessPoint& accessPoint) const
{
    if(isNull() || accessPoint.isNull())
    {
        return false;
    }
    const char* apPath = getAccessPointPath();
    return strcmp(apPath, accessPoint.getPath()) == 0
            && strcmp(apPath, "") != 0; 
}

/*
 * Get a unique ID string for this connection.
 */
const char* NMPPActiveConnection::getUUID() const
{
    const char* uuid = "";
    NMActiveConnectionPtr connection(NM_ACTIVE_CONNECTION(getGObject()));
    if(connection != nullptr)
    {
        uuid = nm_active_connection_get_uuid(connection);
    }
    return uuid;
}

/*
 * Get the connection's NetworkManager ID string.
 */
const char* NMPPActiveConnection::getID() const
{
    const char* conId = "";
    NMActiveConnectionPtr connection(NM_ACTIVE_CONNECTION(getGObject()));
    if(connection != nullptr)
    {
        conId = nm_active_connection_get_id(connection);
    }
    return conId;
}

/*
 * Get this object's active connection state.
 */
NMActiveConnectionState NMPPActiveConnection::getConnectionState() const
{
    NMActiveConnectionState state = NM_ACTIVE_CONNECTION_STATE_UNKNOWN;
    NMActiveConnectionPtr connection(NM_ACTIVE_CONNECTION(getGObject()));
    if(connection != nullptr)
    {
        state = nm_active_connection_get_state(connection);
    }
    return state;
}
