/*
 Stream.cpp - adds parsing methods to Stream class
 Copyright (c) 2008 David A. Mellis.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Created July 2011
 parsing functions based on TextFinder library by Michael Margolis
 */

#include "Stream.h"
#include "Arduino.h"

#define PARSE_TIMEOUT 1000  // Default number of milli-seconds to wait
#define NO_SKIP_CHAR  1  // A magic char not found in a valid ASCII numeric field

// Private method to read stream with timeout
int Stream::timedRead()
{
    int c;
    _startMillis = millis();
    do
    {
        c = read();
        if (c >= 0) return c;
    }
    while(millis() - _startMillis < _timeout);
    return -1;     // -1 indicates timeout
}

// Private method to peek stream with timeout
int Stream::timedPeek()
{
    int c;
    _startMillis = millis();
    do
    {
        c = peek();
        if (c >= 0) return c;
    }
    while(millis() - _startMillis < _timeout);
    return -1;     // -1 indicates timeout
}

// Returns peek of the next digit in the stream or -1. If timeout
// discards non-numeric characters
int Stream::peekNextDigit()
{
    int c;
    while (1)
    {
        c = timedPeek();
        if (c < 0) return c;  // timeout
        if (c == '-') return c;
        if (c >= '0' && c <= '9') return c;
        read();  // discard non-numeric
    }
}

// Public Methods
//////////////////////////////////////////////////////////////

void Stream::setTimeout(unsigned long timeout)  // Sets the maximum number of milliseconds to wait
{
    _timeout = timeout;
}

// Find returns true if the target string is found
bool  Stream::find(char *target)
{
    return findUntil(target, (char*)"");
}

// Reads data from the stream until the target string of given length is found
// Returns true if target string is found, false if timed out
bool Stream::find(char *target, size_t length)
{
    return findUntil(target, length, NULL, 0);
}

// As find but search ends if the terminator string is found
bool  Stream::findUntil(char *target, char *terminator)
{
    return findUntil(target, strlen(target), terminator, strlen(terminator));
}

// Reads data from the stream until the target string of the given length is found
// Search terminated if the terminator string is found
// Returns true if target string is found, false if terminated or timed out
bool Stream::findUntil(char *target, size_t targetLen, char *terminator, size_t termLen)
{
    size_t index = 0;  // Maximum target string length is 64k bytes!
    size_t termIndex = 0;
    int c;

    if( *target == 0)
        return true;   // Return true if target is a null string
    while( (c = timedRead()) > 0)
    {

        if(c != target[index])
            index = 0; // Reset index if any char does not match

        if( c == target[index])
        {
            ////// Serial.print("found "); Serial.write(c); Serial.print("index now"); Serial.println(index+1);
            if(++index >= targetLen)   // Return true if all chars in the target match
            {
                return true;
            }
        }

        if(termLen > 0 && c == terminator[termIndex])
        {
            if(++termIndex >= termLen)
                return false;       // Return false if terminate string found before target string
        }
        else
            termIndex = 0;
    }
    return false;
}


// Returns the first valid (long) integer value from the current position.
// Initial characters that are not digits (or the minus sign) are skipped
// Function is terminated by the first character that is not a digit.
long Stream::parseInt()
{
    return parseInt(NO_SKIP_CHAR); // Terminate on first non-digit character (or timeout)
}

// As above but a given skipChar is ignored
// This allows format characters (typically commas) in values to be ignored
long Stream::parseInt(char skipChar)
{
    boolean isNegative = false;
    long value = 0;
    int c;

    c = peekNextDigit();
    // Ignore non numeric leading characters
    if(c < 0)
        return 0; // Zero returned if timeout

    do
    {
        if(c == skipChar)
            ; // Ignore this charactor
        else if(c == '-')
            isNegative = true;
        else if(c >= '0' && c <= '9')        // Is c a digit?
            value = value * 10 + c - '0';
        read();  // Consume the character we got with peek
        c = timedPeek();
    }
    while( (c >= '0' && c <= '9') || c == skipChar );

    if(isNegative)
        value = -value;
    return value;
}


// As parseInt but returns a floating point value
float Stream::parseFloat()
{
    return parseFloat(NO_SKIP_CHAR);
}

// As above but the given skipChar is ignored
// This allows format characters (typically commas) in values to be ignored
float Stream::parseFloat(char skipChar)
{
    boolean isNegative = false;
    boolean isFraction = false;
    long value = 0;
    int c;
    float fraction = 1.0;

    c = peekNextDigit();
    // Ignore non numeric leading characters
    if(c < 0)
        return 0; // Zero returned if timeout

    do
    {
        if(c == skipChar)
            ; // Ignore
        else if(c == '-')
            isNegative = true;
        else if (c == '.')
            isFraction = true;
        else if(c >= '0' && c <= '9')         // Is c a digit?
        {
            value = value * 10 + c - '0';
            if(isFraction)
                fraction *= 0.1;
        }
        read();  // Consume the character we got with peek
        c = timedPeek();
    }
    while( (c >= '0' && c <= '9')  || c == '.' || c == skipChar );

    if(isNegative)
        value = -value;
    if(isFraction)
        return value * fraction;
    else
        return value;
}

// Read characters from stream into buffer
// Terminates if length characters have been read, or timeout (see setTimeout)
// Returns the number of characters placed in the buffer
// The buffer is NOT null terminated.
//
size_t Stream::readBytes(char *buffer, size_t length)
{
    size_t count = 0;
    while (count < length)
    {
        int c = timedRead();
        if (c < 0) break;
        *buffer++ = (char)c;
        count++;
    }
    return count;
}


// As readBytes with terminator character
// Terminates if length characters have been read, timeout, or if the terminator character  detected
// Returns the number of characters placed in the buffer (0 means no valid data found)

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length)
{
    if (length < 1) return 0;
    size_t index = 0;
    while (index < length)
    {
        int c = timedRead();
        if (c < 0 || c == terminator) break;
        *buffer++ = (char)c;
        index++;
    }
    return index; // Return number of characters, not including null terminator
}

String Stream::readString()
{
    String ret;
    int c = timedRead();
    while (c >= 0)
    {
        ret += (char)c;
        c = timedRead();
    }
    return ret;
}

String Stream::readStringUntil(char terminator)
{
    String ret;
    int c = timedRead();
    while (c >= 0 && c != terminator)
    {
        ret += (char)c;
        c = timedRead();
    }
    return ret;
}


int Stream::findMulti( struct Stream::MultiTarget *targets, int tCount)
{
    // Any zero length target string automatically matches and would make
    // A mess of the rest of the algorithm.
    for (struct MultiTarget *t = targets; t < targets + tCount; ++t)
    {
        if (t->len <= 0)
            return t - targets;
    }

    while (1)
    {
        int c = timedRead();
        if (c < 0)
            return -1;

        for (struct MultiTarget *t = targets; t < targets + tCount; ++t)
        {
            // The simple case is if we match, deal with that first.
            if (c == t->str[t->index])
            {
                if (++t->index == t->len)
                    return t - targets;
                else
                    continue;
            }

            // If not we need to walk back and see if we could have matched further
            // Down the stream (ie '1112' doesn't match the first position in '11112'
            // but it will match the second position so we can't just reset the current
            // index to 0 when we find a mismatch.
            if (t->index == 0)
                continue;

            int origIndex = t->index;
            do
            {
                --t->index;
                // First check if current char works against the new current index
                if (c != t->str[t->index])
                    continue;

                // If it's the only char then we're good, nothing more to check
                if (t->index == 0)
                {
                    t->index++;
                    break;
                }

                // Otherwise we need to check the rest of the found string
                int diff = origIndex - t->index;
                size_t i;
                for (i = 0; i < t->index; ++i)
                {
                    if (t->str[i] != t->str[i + diff])
                        break;
                }

                // If we successfully got through the previous loop then our current
                // index is good.
                if (i == t->index)
                {
                    t->index++;
                    break;
                }

                // Otherwise we just try the next index
            }
            while (t->index);
        }
    }
    // Unreachable
//  Return -1;
}
