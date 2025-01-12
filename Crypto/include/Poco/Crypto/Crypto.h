//
// Crypto.h
//
// Library: Crypto
// Package: CryptoCore
// Module:  Crypto
//
// Basic definitions for the Poco Crypto library.
// This file must be the first file included by every other Crypto
// header file.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Crypto_Crypto_INCLUDED
#define Crypto_Crypto_INCLUDED


#if defined(__APPLE__)
// OS X 10.7 deprecates some OpenSSL functions
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" 
#endif


#include "Poco/Foundation.h"
#include <openssl/opensslv.h>


enum RSAPaddingMode
	/// The padding mode used for RSA public key encryption.
{
	RSA_PADDING_PKCS1,
		/// PKCS #1 v1.5 padding. This currently is the most widely used mode. 
		
	RSA_PADDING_PKCS1_OAEP,
		/// EME-OAEP as defined in PKCS #1 v2.0 with SHA-1, MGF1 and an empty 
		/// encoding parameter. This mode is recommended for all new applications.
		
	RSA_PADDING_NONE
		/// Raw RSA encryption. This mode should only be used to implement cryptographically 
		/// sound padding modes in the application code. Encrypting user data directly with RSA 
		/// is insecure. 
};


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the Crypto_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// Crypto_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32)
	#if defined(POCO_DLL)
		#if defined(Crypto_EXPORTS)
			#define Crypto_API __declspec(dllexport)
		#else
			#define Crypto_API __declspec(dllimport)
		#endif
	#endif
#endif


#if !defined(Crypto_API)
	#if !defined(POCO_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define Crypto_API __attribute__ ((visibility ("default")))
	#else
		#define Crypto_API
	#endif
#endif


//
// Automatically link Crypto and OpenSSL libraries.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS)
		#if defined(POCO_INTERNAL_OPENSSL_MSVC_VER)
			#if defined(POCO_EXTERNAL_OPENSSL)
				#pragma warning "External OpenSSL defined but internal headers used - possible mismatch!"
			#endif // POCO_EXTERNAL_OPENSSL
			#if !defined(_DEBUG)
				#define POCO_DEBUG_SUFFIX ""
				#if !defined (_DLL)
					#define POCO_STATIC_SUFFIX "mt"
				#else // _DLL
					#define POCO_STATIC_SUFFIX ""
				#endif
			#else // _DEBUG
				#define POCO_DEBUG_SUFFIX "d"
				#if !defined (_DLL)
					#define POCO_STATIC_SUFFIX "mt"
				#else // _DLL
					#define POCO_STATIC_SUFFIX ""
				#endif
			#endif
			#pragma comment(lib, "libcrypto" POCO_STATIC_SUFFIX POCO_DEBUG_SUFFIX ".lib")
			#pragma comment(lib, "libssl" POCO_STATIC_SUFFIX POCO_DEBUG_SUFFIX ".lib")
			#if !defined(_WIN64) && !defined (_DLL) && \
						(POCO_INTERNAL_OPENSSL_MSVC_VER == 120) && \
						(POCO_MSVC_VERSION < POCO_INTERNAL_OPENSSL_MSVC_VER)
				#pragma comment(lib, "libPreVS2013CRT" POCO_STATIC_SUFFIX POCO_DEBUG_SUFFIX ".lib")
			#endif
			#if !defined (_DLL) && (POCO_MSVS_VERSION >= 2015)
				#pragma comment(lib, "legacy_stdio_definitions.lib")
				#pragma comment(lib, "legacy_stdio_wide_specifiers.lib")
			#endif
		#endif // POCO_INTERNAL_OPENSSL_MSVC_VER
		#if !defined(Crypto_EXPORTS)
			#pragma comment(lib, "PocoCrypto" POCO_LIB_SUFFIX)
		#endif
	#endif // POCO_NO_AUTOMATIC_LIBS
#endif


namespace Poco {
namespace Crypto {


void Crypto_API initializeCrypto();
	/// Initialize the Crypto library, as well as the underlying OpenSSL
	/// libraries, by calling OpenSSLInitializer::initialize().
	///
	/// Should be called before using any class from the Crypto library.
	/// The Crypto library will be initialized automatically, through  
	/// OpenSSLInitializer instances held by various Crypto classes
	/// (Cipher, CipherKey, RSAKey, X509Certificate).
	/// However, it is recommended to call initializeCrypto()
	/// in any case at application startup.
	///
	/// Can be called multiple times; however, for every call to
	/// initializeCrypto(), a matching call to uninitializeCrypto()
	/// must be performed.
	

void Crypto_API uninitializeCrypto();
	/// Uninitializes the Crypto library by calling 
	/// OpenSSLInitializer::uninitialize().


} } // namespace Poco::Crypto


#endif // Crypto_Crypto_INCLUDED
