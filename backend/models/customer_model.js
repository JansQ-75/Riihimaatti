const db = require('../database');

const customer = {
  //Get all customer data
  getAll: function (callback) {
    return db.query('SELECT * FROM customer;', callback);
  },
  //Get custormer by id
  getById: function (idcustomer, callback) {
    return db.query(
      'SELECT * FROM customer WHERE idcustomer=?',
      [idcustomer],
      callback,
    );
  },
  //Add a customer
  add: function (customer_data, callback) {
    return db.query(
      'INSERT INTO customer(fname, lname, address, phone) VALUES(?,?,?,?)',
      [
        customer_data.fname,
        customer_data.lname,
        customer_data.address,
        customer_data.phone,
      ],
      callback,
    );
  },
  /**
   * Update Customer data.
   * Empty/Voided fields are kept
   *
   * @param {number} idcustomer - Customer id
   * @param {Object} customer_data - Object with to-be-updated data
   * @param {Function} callback
   * @returns
   */
  update: function (idcustomer, customer_data, callback) {
    const updates = [];
    const values = [];

    if (customer_data.fname) {
      updates.push('fname = ?');
      values.push(customer_data.fname);
    }
    if (customer_data.lname) {
      updates.push('lname = ?');
      values.push(customer_data.lname);
    }
    if (customer_data.address) {
      updates.push('address = ?');
      values.push(customer_data.address);
    }
    if (customer_data.phone) {
      updates.push('phone = ?');
      values.push(customer_data.phone);
    }
    if (customer_data.picture) {
      updates.push('picture = ?');
      values.push(customer_data.picture);
    }

    values.push(idcustomer);
    return db.query(
      `
      UPDATE customer
      SET ${updates.join(', ')}
      WHERE idcustomer = ?`,
      values,
      callback,
    );
  },
  /**
   * Remove a customer - Admin access only
   */
  delete: function (idcustomer, callback) {
    return db.query(
      'DELETE FROM customer WHERE idcustomer=?',
      [idcustomer],
      callback,
    );
  },

  validateCustomerAccess: function (req, res, next) {
    if (req.isAdmin) {
      return next();
    }
    const query = `
        SELECT c.idcustomer
        FROM card c
        WHERE c.cardnumber = ? AND c.idcustomer = ?
      `;
    console.log(req.cardnumber);

    db.query(query, [req.cardnumber, req.params.idcustomer], (err, result) => {
      if (err)
        return res
          .status(500)
          .json({ error: `500: It's not you, it's me problem` });
      console.log(req.isAdmin);

      if (!result.length)
        return res.status(403).json({ error: `Access denied! Stop snooping!` });

      next();
    });
  },
};

module.exports = customer;
