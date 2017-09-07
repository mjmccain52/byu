// Decompiled by DJ v3.11.11.95 Copyright 2009 Atanas Neshkov  Date: 11/5/2009 10:17:01 AM
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   TokenizerImpl.java

package cs235.xml;

import java.io.*;
import java.util.ArrayList;

// Referenced classes of package cs235.xml:
//            Tokenizer, XMLException

class TokenizerImpl
    implements Tokenizer
{

    public TokenizerImpl(InputStream _input)
    {
        tokenType = 0;
        input = new BufferedReader(new InputStreamReader(_input));
        attrNames = new ArrayList();
        attrVals = new ArrayList();
    }

    private void resetState(boolean resetTagName)
    {
        if(resetTagName)
            tagName = null;
        attrNames.clear();
        attrVals.clear();
        text = null;
    }

    public int nextToken()
        throws IOException, XMLException
    {
        if(tokenType == 0)
            parseText();
        switch(tokenType)
        {
        case 3: // '\003'
            resetState(true);
            parseTag();
            break;

        case 4: // '\004'
            break;

        case 1: // '\001'
        case 2: // '\002'
            if(haveEndTag)
            {
                resetState(false);
                tokenType = 2;
                haveEndTag = false;
                break;
            }
            resetState(true);
            parseText();
            if(tokenType == 3 && text.equals(""))
            {
                resetState(true);
                parseTag();
            }
            break;

        default:
            throw new IllegalStateException();
        }
        return tokenType;
    }

    public int getTokenType()
    {
        return tokenType;
    }

    public String getTagName()
    {
        if(tokenType != 1 && tokenType != 2)
            throw new IllegalStateException();
        else
            return tagName;
    }

    public String getAttributeValue(String name)
    {
        if(tokenType != 1)
            throw new IllegalStateException();
        if(name == null)
            throw new IllegalArgumentException();
        int idx = getAttrIdx(name);
        if(idx >= 0)
            return (String)attrVals.get(idx);
        else
            return null;
    }

    public int getAttributeCount()
    {
        if(tokenType != 1)
            throw new IllegalStateException();
        else
            return attrNames.size();
    }

    public String getAttributeName(int i)
    {
        if(tokenType != 1)
            throw new IllegalStateException();
        if(i < 0 || i >= getAttributeCount())
            throw new IllegalArgumentException();
        else
            return (String)attrNames.get(i);
    }

    public String getAttributeValue(int i)
    {
        if(tokenType != 1)
            throw new IllegalStateException();
        if(i < 0 || i >= getAttributeCount())
            throw new IllegalArgumentException();
        else
            return (String)attrVals.get(i);
    }

    public String getText()
    {
        if(tokenType != 3)
            throw new IllegalStateException();
        else
            return text;
    }

    private int getAttrIdx(String name)
    {
        if(attrNames != null)
        {
            for(int i = 0; i < attrNames.size(); i++)
                if(attrNames.get(i).equals(name))
                    return i;

        }
        return -1;
    }

    private int readOptionalChar(boolean skipWS)
        throws IOException
    {
        int n;
        char c;
        do
        {
            n = input.read();
            if(n < 0)
                break;
            c = (char)n;
        } while(skipWS && Character.isWhitespace(c));
        return n;
    }

    private int readOptionalChar()
        throws IOException
    {
        return readOptionalChar(false);
    }

    private char readChar(boolean skipWS)
        throws IOException, XMLException
    {
        int n = readOptionalChar(skipWS);
        if(n < 0)
            throw new XMLException("unexpected end of document");
        else
            return (char)n;
    }

    private char readChar()
        throws IOException, XMLException
    {
        return readChar(false);
    }

    private void skipUntil(char terminator)
        throws IOException, XMLException
    {
        char c;
        do
            c = readChar();
        while(c != terminator);
    }

    private void match(char expected, boolean skipWS)
        throws IOException, XMLException
    {
        char c = readChar(skipWS);
        if(c != expected)
            throw new XMLException("unexpected character: expected [" + expected + "], got [" + c + "]");
        else
            return;
    }

    private void match(char expected)
        throws IOException, XMLException
    {
        match(expected, false);
    }

    private void parseTag()
        throws IOException, XMLException
    {
        boolean isStartTag = true;
        char c = readChar();
        if(c == '/')
        {
            isStartTag = false;
            c = readChar();
        }
        tagName = "";
        for(; Character.isLetterOrDigit(c); c = readChar())
            tagName += c;

        String INVALID_TAG = "invalid tag: <" + (isStartTag ? "" : "/") + tagName + ">";
        if(tagName.length() == 0)
            throw new XMLException(INVALID_TAG);
        if(isStartTag)
        {
            tokenType = 1;
            switch(c)
            {
            case 47: // '/'
                match('>', false);
                haveEndTag = true;
                break;

            default:
                if(!Character.isWhitespace(c))
                    throw new XMLException(INVALID_TAG);
                haveEndTag = parseAttrs();
                break;

            case 62: // '>'
                break;
            }
        } else
        {
            tokenType = 2;
            switch(c)
            {
            default:
                if(!Character.isWhitespace(c))
                    throw new XMLException(INVALID_TAG);
                match('>', true);
                break;

            case 62: // '>'
                break;
            }
        }
    }

    private boolean parseAttrs()
        throws IOException, XMLException
    {
        String INVALID_TAG = "invalid tag: <" + tagName + ">";
        char c = readChar(true);
        do
        {
            if(c == '>')
                return false;
            if(c == '/')
            {
                match('>', false);
                return true;
            }
            String attrName = "";
            for(; Character.isLetterOrDigit(c); c = readChar(false))
                attrName = attrName + c;

            if(attrName.length() == 0)
                throw new XMLException(INVALID_TAG);
            String INVALID_ATTR = "invalid attribute: <" + tagName + ">, " + attrName;
            if(Character.isWhitespace(c))
                c = readChar(true);
            if(c != '=')
                throw new XMLException(INVALID_ATTR);
            String attrVal = "";
            c = readChar(true);
            if(c == '\'' || c == '"')
            {
                char delimiter = c;
                for(c = readChar(false); c != delimiter; c = readChar(false))
                    attrVal = attrVal + c;

                c = readChar(true);
            } else
            {
                throw new XMLException(INVALID_ATTR);
            }
            attrNames.add(attrName);
            attrVals.add(attrVal);
        } while(true);
    }

    private void parseText()
        throws IOException, XMLException
    {
        String data = "";
        int n;
        for(n = readOptionalChar(); n != -1 && (char)n != '<'; n = readOptionalChar())
            data = data + (char)n;

        if(n != -1)
        {
            tokenType = 3;
            text = data;
        } else
        {
            tokenType = 4;
        }
    }

    private Reader input;
    private int tokenType;
    private String tagName;
    private ArrayList attrNames;
    private ArrayList attrVals;
    private String text;
    private boolean haveEndTag;
}
