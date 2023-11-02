#pragma once
#include <string>
using keyword_t = const std::string;

struct Keywords
{
    keyword_t log{"login:"};         // login string
    keyword_t pas{"password:"};      // password string

    keyword_t name{"username:"};     // user name string

    keyword_t timesend{"timesend:"}; // timesend string
    keyword_t mess{"message:"};      // message string
    keyword_t sep{" "};              // separator

    // client to server
    keyword_t itLogon{"&itLoon&"}; // logon cmd
    keyword_t itRegistration{"&itRegn&"}; // registration cmd
    keyword_t itMessage{"&itMess&"}; // message cmd
    keyword_t itLogout{"&itLout&"}; // logout cmd
    keyword_t itExit{"&itExit&"}; // end sesion cmd

    keyword_t itCompName{"&itCmnm&"}; // select companion cmd

    keyword_t itGetUsernames{"&itGtUn&"}; // get registered usernames cmd
    keyword_t itContinueUsernames{"&itCntu&"}; // continue send usernames cmd
    keyword_t itGetMessages{"&itGtMs&"}; // get last messages cmd
    keyword_t itContinueMassages{"&itCntm&"}; // continue send message cmd

    // server to client packages
    keyword_t itUsernames{"&itUnms&"}; // it is usernames package sts
    keyword_t itUsernamesEnd{"&itUnme&"}; // it is usernames package end sts
    keyword_t itMessages{"&itMsgs&"}; // it is last messages sts
    keyword_t itMessagesEnd{"&itMsge&"}; // it is last messages end sts
    keyword_t itEndOfPackage{"&itEnPa&"}; // it end of package sts
};
