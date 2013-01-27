#ifndef __DEFAULTFACTORYERRORPOLICY__
#define __DEFAULTFACTORYERRORPOLICY__

#include <utils/traits/parametertrait.hpp>

#include <stdexcept>

template<class IdentifierType, class ProductType> class DefaultFactoryErrorPolicy
{
public:
	class Exception : public std::exception
	{
	public:
        Exception(typename ParameterTrait<IdentifierType>::const_reference id) : std::exception(), m_unknownId(id)
		{}
		
		virtual const char* what()
		{
			return "Type inconnu passé à la factory.";
		}
		
        typename ParameterTrait<IdentifierType>::const_reference getId() const
		{
			return m_unknownId;
		}
		
	private:
		IdentifierType m_unknownId;
	};
	
protected:
    static ProductType* onUnknownType(typename ParameterTrait<IdentifierType>::const_reference id)
	{
		throw Exception(id);
	}
};

#endif
