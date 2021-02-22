#pragma once
#include<sstream>

using namespace std;

class Data : public std::basic_string<uint8_t>{
	public:
		/******************************************************************************/
		// --- Constructor / Destructor --- //
		/******************************************************************************/

		/**
		 * @brief Default constructor of Data
		 */
		Data();

		/**
		 * @brief Constructor of data with available pointer to data
		 */
		Data(const uint8_t* pData, uint32_t dataSize);

		/**
		 * @brief Copy constructor
		 */
		Data(const Data& otherData);

		/**
		 * @brief Copy constructor
		 */
		explicit Data(const std::basic_string<uint8_t>& otherData);

		/**
		 * @brief Destructor
		 */
		virtual ~Data();

		/******************************************************************************/
		// --- Functions --- //
		/******************************************************************************/

		/**
		 * @fn readFromfile
		 * @brief Reads the content from the specified filename into the data
		 * structure.
		 * @param filename The path and name of the file which shall be read.
		 * @throws NFIQException
		 */
		bool readFromFile(const std::string& filename);

};

