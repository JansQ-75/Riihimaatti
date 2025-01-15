const express = require('express');
const router = express.Router();

/* GET resource. */
router.get('/', function (req, res, next) {
  const transactions = db.query('SELECT * FROM student', callback);

  res.send(transactions);
});

module.exports = router;
