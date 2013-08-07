#ifndef RPCMETHODS_H_
#define RPCMETHODS_H_

#include <vector>
#include <memory>

#include "RPCServer.h"
#include "RPCVariable.h"
#include "RPCMethod.h"

namespace RPC
{
class RPCSystemGetCapabilities : public RPCMethod
{
public:
	RPCSystemGetCapabilities()
	{
		setHelp("Lists server's XML RPC capabilities.");
		addSignature(RPCVariableType::rpcStruct, std::vector<RPCVariableType>());
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCSystemListMethods : public RPCMethod
{
public:
	RPCSystemListMethods(std::shared_ptr<RPCServer> server)
	{
		_server = server;
		setHelp("Lists all XML RPC methods.");
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>());
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
private:
	std::shared_ptr<RPCServer> _server;
};

class RPCSystemMethodHelp : public RPCMethod
{
public:
	RPCSystemMethodHelp(std::shared_ptr<RPCServer> server)
	{
		_server = server;
		setHelp("Returns a description of the method.");
		addSignature(RPCVariableType::rpcString, std::vector<RPCVariableType>{RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
private:
	std::shared_ptr<RPCServer> _server;
};

class RPCSystemMethodSignature : public RPCMethod
{
public:
	RPCSystemMethodSignature(std::shared_ptr<RPCServer> server)
	{
		_server = server;
		setHelp("Returns the method's signature.");
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>{RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
private:
	std::shared_ptr<RPCServer> _server;
};

class RPCSystemMulticall : public RPCMethod
{
public:
	RPCSystemMulticall(std::shared_ptr<RPCServer> server)
	{
		_server = server;
		setHelp("Calls multiple XML RPC methods.");
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>{RPCVariableType::rpcArray});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
private:
	std::shared_ptr<RPCServer> _server;
};

class RPCAddDevice : public RPCMethod
{
public:
	RPCAddDevice()
	{
		addSignature(RPCVariableType::rpcStruct, std::vector<RPCVariableType>{RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCAddLink : public RPCMethod
{
public:
	RPCAddLink()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcString});
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCDeleteDevice : public RPCMethod
{
public:
	RPCDeleteDevice()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcInteger});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCDeleteMetadata : public RPCMethod
{
public:
	RPCDeleteMetadata()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString});
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetAllMetadata : public RPCMethod
{
public:
	RPCGetAllMetadata()
	{
		addSignature(RPCVariableType::rpcVariant, std::vector<RPCVariableType>{RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
private:
	RPCDecoder _rpcDecoder;
};

class RPCGetDeviceDescription : public RPCMethod
{
public:
	RPCGetDeviceDescription()
	{
		addSignature(RPCVariableType::rpcStruct, std::vector<RPCVariableType>{RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetInstallMode : public RPCMethod
{
public:
	RPCGetInstallMode()
	{
		addSignature(RPCVariableType::rpcInteger, std::vector<RPCVariableType>());
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetKeyMismatchDevice : public RPCMethod
{
public:
	RPCGetKeyMismatchDevice()
	{
		addSignature(RPCVariableType::rpcString, std::vector<RPCVariableType>{RPCVariableType::rpcBoolean});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetLinkInfo : public RPCMethod
{
public:
	RPCGetLinkInfo()
	{
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetLinkPeers : public RPCMethod
{
public:
	RPCGetLinkPeers()
	{
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>{RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetLinks : public RPCMethod
{
public:
	RPCGetLinks()
	{
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>());
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>{RPCVariableType::rpcString});
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcInteger});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetMetadata : public RPCMethod
{
public:
	RPCGetMetadata()
	{
		addSignature(RPCVariableType::rpcVariant, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
private:
	RPCDecoder _rpcDecoder;
};

class RPCGetParamsetDescription : public RPCMethod
{
public:
	RPCGetParamsetDescription()
	{
		addSignature(RPCVariableType::rpcStruct, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetParamsetId : public RPCMethod
{
public:
	RPCGetParamsetId()
	{
		addSignature(RPCVariableType::rpcString, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetParamset : public RPCMethod
{
public:
	RPCGetParamset()
	{
		addSignature(RPCVariableType::rpcStruct, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetServiceMessages : public RPCMethod
{
public:
	RPCGetServiceMessages()
	{
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>{RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCGetValue : public RPCMethod
{
public:
	RPCGetValue()
	{
		addSignature(RPCVariableType::rpcVariant, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCInit : public RPCMethod
{
public:
	RPCInit()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCListBidcosInterfaces : public RPCMethod
{
public:
	RPCListBidcosInterfaces()
	{
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>());
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCListDevices : public RPCMethod
{
public:
	RPCListDevices()
	{
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>());
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCListTeams : public RPCMethod
{
public:
	RPCListTeams()
	{
		addSignature(RPCVariableType::rpcArray, std::vector<RPCVariableType>());
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCLogLevel : public RPCMethod
{
public:
	RPCLogLevel()
	{
		addSignature(RPCVariableType::rpcInteger, std::vector<RPCVariableType>{RPCVariableType::rpcInteger});
		addSignature(RPCVariableType::rpcInteger, std::vector<RPCVariableType>());
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCPutParamset : public RPCMethod
{
public:
	RPCPutParamset()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcStruct});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCRemoveLink : public RPCMethod
{
public:
	RPCRemoveLink()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCSetLinkInfo : public RPCMethod
{
public:
	RPCSetLinkInfo()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCSetMetadata : public RPCMethod
{
public:
	RPCSetMetadata()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcVariant});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
private:
	RPCEncoder _rpcEncoder;
};

class RPCSetInstallMode : public RPCMethod
{
public:
	RPCSetInstallMode()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcBoolean});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCSetTeam : public RPCMethod
{
public:
	RPCSetTeam()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString});
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

class RPCSetValue : public RPCMethod
{
public:
	RPCSetValue()
	{
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString, RPCVariableType::rpcVariant});
		addSignature(RPCVariableType::rpcVoid, std::vector<RPCVariableType>{RPCVariableType::rpcString, RPCVariableType::rpcString});
	}
	std::shared_ptr<RPCVariable> invoke(std::shared_ptr<std::vector<std::shared_ptr<RPCVariable>>> parameters);
};

} /* namespace RPC */
#endif /* RPCMETHODS_H_ */
