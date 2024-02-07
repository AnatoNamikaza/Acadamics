import React, { Component } from 'react';
import PropTypes from 'prop-types';
import { connect } from 'react-redux';
import uuid from 'uuid-v4';
import { Row, Col } from 'antd';
import * as productActionsCreator from '../../actions/products';
import Product from '../product';
import styles from './home.scss';

class Home extends Component {
  static propTypes = {
    products: PropTypes.array,
    fetchProducts: PropTypes.func.isRequired,
  };

  static defaultProps = {
    products: [],
  };

  componentDidMount() {
    const { fetchProducts } = this.props;

    fetchProducts();
  }

  render() {
    const { products } = this.props;
    const NO_OF_ITEMS = 4;

    return (
      <div className={styles.home}>
        {Array(Math.ceil(products.length / NO_OF_ITEMS))
          .fill()
          .map((_, i) =>
            products.slice(i * NO_OF_ITEMS, (i * NO_OF_ITEMS) + NO_OF_ITEMS))
          .map(row => (
            <Row key={uuid()} gutter={16}>
              {row.map(product => (
                <Col key={product.id} span={24 / NO_OF_ITEMS}>
                  <Product product={product} />
                </Col>
              ))}
            </Row>
          ))}
        {!products.length && (
          <div className={styles.emptyView}>No product available</div>
        )}
      </div>
    );
  }
}

const mapStateToProps = state => ({
  products: state.products.all,
});

export default connect(mapStateToProps, productActionsCreator)(Home);
