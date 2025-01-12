//
// EVServerRequest.h
//
// Library: evnet
// Package: HTTPServer
// Module:  EVServerRequest
//
// Definition of the EVServerRequest class.
//


#ifndef EVNet_EVServerRequest_INCLUDED
#define EVNet_EVServerRequest_INCLUDED
#include "Poco/Net/Net.h"


namespace Poco {
namespace evnet {

class Net_API EVServerRequest
	/// This is a marker class for any server reuqest
	/// representing server-side requests.
	///
{

public:
	EVServerRequest();
		/// Creates the EVServerRequest, using the
		/// given EVServerSession.

	~EVServerRequest();
		/// Destroys the EVServerRequest.
		
};

} } // namespace Poco::evnet


#endif // EVNet_EVServerRequest_INCLUDED
