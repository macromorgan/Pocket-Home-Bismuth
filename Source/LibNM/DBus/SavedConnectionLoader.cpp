#include "LibNM/DBus/SavedConnectionLoader.h"
#include "LibNM/AccessPoint.h"

/* The NetworkManager's DBus path: */
const constexpr char* busName = "org.freedesktop.NetworkManager";
/* SavedConnectionLoader's DBus interface name: */
const constexpr char* interface = "org.freedesktop.NetworkManager.Settings";
/* SavedConnectionLoader's DBus interface path: */
const constexpr char* path = "/org/freedesktop/NetworkManager/Settings";

/* DBus listConnections method key: */
const constexpr char* listConnectionMethod = "ListConnections";

/*
 * Connects to NetworkManager over DBus to initialize the saved connection list.
 */
LibNM::SavedConnectionLoader::SavedConnectionLoader() :
GLib::DBusProxy(busName, path, interface) 
{ 
    juce::StringArray paths = getConnectionPaths();
    for(const juce::String& path : paths)
    {
        connectionList.add(SavedConnection(path.toRawUTF8()));
    }
    DBG("SavedConnectionLoader::" << __func__  << ": Found "
            << connectionList.size() << " connections.");
}

/*
 * Reads all connection paths from NetworkManager, and returns all the wifi
 * connections as SavedConnection objects.
 */
juce::Array<LibNM::SavedConnection> 
LibNM::SavedConnectionLoader::getWifiConnections() const
{
    juce::Array<SavedConnection> connections;
    for(const SavedConnection& con : connectionList)
    {
        if(con.isWifiConnection())
        {
            connections.add(con);
        }
    }
    return connections;
}
    
/*
 * Checks saved connection paths to see if one exists at the given path.
 */
bool LibNM::SavedConnectionLoader::connectionExists
(const juce::String& connectionPath) const
{
    return connectionPaths.contains(connectionPath);
}
 
/*
 * Finds a saved connection from its DBus path.
 */
LibNM::SavedConnection LibNM::SavedConnectionLoader::getConnection
(const juce::String& connectionPath)
{
    if(!connectionExists(connectionPath))
    {
        updateSavedConnections();
    }
    if(connectionExists(connectionPath))
    {
        for(const SavedConnection& con : connectionList)
        {
            if(con.getPath() == connectionPath)
            {
                return con;
            }
        }
    }
    SavedConnection emptyConn;
    return emptyConn;
}
  
/*
 * Finds all saved connections that are compatible with a given wifi access 
 * point.
 */
juce::Array<LibNM::SavedConnection> 
LibNM::SavedConnectionLoader::findConnectionsForAP
(const AccessPoint& accessPoint) const
{
    using juce::Array;
    Array<SavedConnection> compatible;
    if(!isNull() && !accessPoint.isNull())
    {
        Array<SavedConnection> wifiCons = getWifiConnections();
        for(const SavedConnection& con : wifiCons)
        {
            if(con.getNMConnection().isCompatibleAccessPoint(accessPoint))
            {
                compatible.add(con);
            }
        }
    }
    return compatible;
}
    
/*
 * Get the list of all available connection paths
 */
inline juce::StringArray 
LibNM::SavedConnectionLoader::getConnectionPaths() const
{
    using namespace VariantConverter;
    using juce::StringArray;
    GVariant* conArrayVar = callMethod(listConnectionMethod);
    if(conArrayVar != nullptr)
    {
        StringArray paths = getValue<StringArray>(conArrayVar);
        g_variant_unref(conArrayVar);
        conArrayVar = nullptr;
        return paths;
    }
    return StringArray();
}

/*
 * Checks the list of saved connections against an updated connection path
 * list, adding any new connections and removing any deleted connections.
 */
void LibNM::SavedConnectionLoader::updateSavedConnections()
{
    connectionPaths = getConnectionPaths();
    juce::Array<SavedConnection> toRemove;
    for(const SavedConnection& saved : connectionList)
    {
        if(!connectionPaths.contains(saved.getPath()))
        {
            toRemove.add(saved);
        }
        else
        {
            connectionPaths.removeString(saved.getPath());
        }
    }
    for(const SavedConnection& removing : toRemove)
    {
        connectionList.removeAllInstancesOf(removing);
    }
    for(const juce::String& path : connectionPaths)
    {
        connectionList.add(SavedConnection(path.toRawUTF8()));
    }
}
