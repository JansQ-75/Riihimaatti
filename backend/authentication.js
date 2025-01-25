const jwt = require('jsonwebtoken');

function authenticateToken(req, res, next) {
  const authHeader = req.headers.authorization;
  const token = authHeader && authHeader.split(' ')[1];
  if (!token) {
    return res.status(401).json({ error: 'Unauthorized: Token required' });
  }

  jwt.verify(token, process.env.JWT_TOKEN, function (err, auth) {
    if (err) {
      return res.sendStatus(403);
    }

    if (auth.cardnumber === '0') {
      req.isAdmin = true;
      return next();
    }
    req.cardnumber = auth.cardnumber;
    return next();
  });
}

/**
 * Simple middleware to check if user was recognized as admin
 *
 * @param {Object} req - Response object
 * @param {Object} res - Response object
 * @param {Function} next - Callback to function proper
 * @returns
 */
function checkAdmin(req, res, next) {
  if (!req.isAdmin) {
    return res
      .status(403)
      .json({ error: 'Forbidden. Admin priviledges required.' });
  }

  next();
}
module.exports = { authenticateToken, checkAdmin };
