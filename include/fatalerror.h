/**
 *  FatalError.h
 * 
 * 
 *  Normally, fatal errors are reported with a call to zend_error().
 * 
 *  However, this will trigger a longjmp(), which will cause objects
 *  constructed in the extension not to be destructed. We use therefore
 *  this FatalError class, which is a normally exception that _does_
 *  cause objects to be destructed.
 * 
 *  When it is caught, right before control is handed back to the Zend
 *  engine, it will turn the exception into a zend_error() call and
 *  thus a longjmp.
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace Php {

/**
 *  Class definition
 */
class FatalError : public Exception
{
public:
    /**
     *  Constructor
     *  @param  message
     */
    FatalError(const std::string &message) : Exception(message) {}
    
    /**
     *  Destructor
     */
    virtual ~FatalError() throw() 
    {
    }

    /**
     *  Is this a native exception (one that was thrown from C++ code)
     *  @return bool
     */
    virtual bool native() const
    {
        // although it is native, we return 0 because it should not persist
        // as exception, but it should live on as zend_error() in stead
        return false;
    }
    
    /**
     *  Report this error as a fatal error
     *  @return bool
     */
    virtual bool report() const override;
};
    
/**
 *  End of namespace
 */
}

