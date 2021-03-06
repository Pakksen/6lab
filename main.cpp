#include "pch.h"
#include "base64.hpp"
#include <iostream>

TEST(EncodeTests, EncodeEmptyString)
{
    EXPECT_EQ("", Encode(""));
}

TEST(EncodeTests, EncodeOneNLengthString)
{
    EXPECT_EQ("Tw", Encode("O"));
    EXPECT_EQ("T08", Encode("OO"));
    EXPECT_EQ("T09Q", Encode("OOP"));
    EXPECT_EQ("T09QIA", Encode("OOP "));
    EXPECT_EQ("T09QIHQ", Encode("OOP t"));
    EXPECT_EQ("T09QIHRv", Encode("OOP to"));
    EXPECT_EQ("T09QIHRvcA", Encode("OOP top"));
}

TEST(EncodeTests, EncodeTwoNLengthString)
{
    EXPECT_EQ("RkU", Encode("FE"));
    EXPECT_EQ("RkVGVQ", Encode("FEFU"));
    EXPECT_EQ("RkVGVSBp", Encode("FEFU i"));
    EXPECT_EQ("RkVGVSBpcyA", Encode("FEFU is "));
    EXPECT_EQ("RkVGVSBpcyB0aA", Encode("FEFU is th"));
    EXPECT_EQ("RkVGVSBpcyB0aGUg", Encode("FEFU is the "));
    EXPECT_EQ("RkVGVSBpcyB0aGUgYmU", Encode("FEFU is the be"));
    EXPECT_EQ("RkVGVSBpcyB0aGUgYmVzdA", Encode("FEFU is the best"));
}

TEST(EncodeTests, EncodeThreeNLengthString)
{
    EXPECT_EQ("V2hv", Encode("Who"));
    EXPECT_EQ("V2hvIGtp", Encode("Who ki"));
    EXPECT_EQ("V2hvIGtpbGxl", Encode("Who kille"));
    EXPECT_EQ("V2hvIGtpbGxlZCBN", Encode("Who killed M"));
    EXPECT_EQ("V2hvIGtpbGxlZCBNYXJr", Encode("Who killed Mark"));
}

TEST(DecodeTests, DecodeEmptyString)
{
    EXPECT_EQ("", Decode(""));
}

TEST(DecodeTests, DecodeOneNLengthReturn)
{
    EXPECT_EQ("H", Decode("SA"));
    EXPECT_EQ("Hi", Decode("SGk"));
    EXPECT_EQ("Hi ", Decode("SGkg"));
    EXPECT_EQ("Hi m", Decode("SGkgbQ"));
    EXPECT_EQ("Hi ma", Decode("SGkgbWE"));
    EXPECT_EQ("Hi man", Decode("SGkgbWFu"));
}

TEST(DecodeTests, DecodeTwoNLengthReturn)
{
    EXPECT_EQ("I'", Decode("SSc"));
    EXPECT_EQ("I'm ", Decode("SSdtIA"));
    EXPECT_EQ("I'm ti", Decode("SSdtIHRp"));
    EXPECT_EQ("I'm tire", Decode("SSdtIHRpcmU"));
    EXPECT_EQ("I'm tired!", Decode("SSdtIHRpcmVkIQ"));
}

TEST(DecodeTests, DecodeThreeNLengthReturn)
{
    EXPECT_EQ("I l", Decode("SSBs"));
    EXPECT_EQ("I love", Decode("SSBsb3Zl"));
    EXPECT_EQ("I love pr", Decode("SSBsb3ZlIHBy"));
    EXPECT_EQ("I love progr", Decode("SSBsb3ZlIHByb2dy"));
    EXPECT_EQ("I love programm", Decode("SSBsb3ZlIHByb2dyYW1t"));
    EXPECT_EQ("I love programming", Decode("SSBsb3ZlIHByb2dyYW1taW5n"));
}

int main(int argc, char** argv)
{
    // ?????? ?????? ???????????????:
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();

    std::string inputString;

    // ????????? ?????? ?????. ?????????? getline(), ????? ????? ???? ? ??????? ? ????????? inputString.
    getline(std::cin, inputString);

    std::cout << std::endl << " E N C O D E (only English)" << std::endl;
    std::cout << Encode(inputString) << std::endl;

    std::cout << std::endl << " D E C O D E " << std::endl;
    std::cout << Decode(Encode(inputString)) << std::endl;
}